/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/yall.h"

#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "yall/utils.h"
#include "yall/writer.h"
#include "yall/message.h"
#include "yall/subsystem.h"
#include "yall/debug.h"

#define WRITER_THREAD_FREQUENCY 60

#include "version.h"
#define YALL_VERSION_STR STRINGIFY(YALL_MAJOR) "." STRINGIFY(YALL_MINOR) \
	"." STRINGIFY(YALL_PATCH)

static uint32_t version = (YALL_MAJOR << 16) | (YALL_MINOR << 8) | YALL_PATCH;
static const char *version_string =
	"yall, Quentin <Naccyde> Deslandes, version " YALL_VERSION_STR;

uint32_t yall_get_version(void)
{
	return version;
}

const char *yall_get_version_string(void)
{
	return version_string;
}

static uint16_t initialized = 0;

yall_error yall_init(void)
{
	yall_error ret = YALL_SUCCESS;

	if (initialized) {
		++initialized;
		ret = YALL_ALREADY_INIT;
		goto end;
	}

	++initialized;

	ret = writer_init();
	if (ret)
		goto err;

	config_setup();

        if ((ret = writer_init(WRITER_THREAD_FREQUENCY)))
                goto err;

end:
	return ret;
err:
	--initialized;
	return ret;
}

uint8_t yall_is_init(void)
{
	return initialized;
}

yall_error yall_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function,
	const char *filename,
	int32_t line,
	const char *format,
	...)
{
	// TODO : prefix structs with "yall"
	yall_error ret = YALL_SUCCESS;
	char *buff = NULL;
	va_list args, args_cpy;
	size_t hdr_len = 0;
	size_t buff_len = 0;
	struct header_content hc = { 0 };
	struct yall_subsystem_params p = { 0 };

	if (! initialized) {
		ret = YALL_NOT_INIT;
		goto end;
	}

	/*
	 * Find the subsystem's parameters. Useless to get the subsystem, or
	 * to know if it is found. If the subsystem is not found, we use the
	 * default parameters.
	 */
	get_subsystem(subsystem, &p);

	if (p.status == yall_subsys_disable) {
		ret = YALL_SUBSYS_DISABLED;
		goto end;
	}

	if (log_level < p.log_level) {
		ret = YALL_LOG_LEVEL_TOO_LOW;
		goto end;
	}

	fill_header_content(&hc, subsystem, log_level, function, filename,
		line);

	va_start(args, format);

	/*
	 * Make a copy of variadic arguments to compute the length of the future
	 * log message.
	 * "+2" is used for '\n' and '\0' at the end of the log message.
	 */
	va_copy(args_cpy, args);
	hdr_len = generate_std_hdr(NULL, 0, &hc);
	buff_len = hdr_len + generate_std_msg(NULL, 0, format, args_cpy) + 2;
	va_end(args_cpy);

	// Allocate the log message buffer
	buff = malloc(buff_len);

	/*
	 * Header generation, hdr_len does not take in account the '\0', so
	 * if we remove the "+1", the header will be cut 1 character too soon.
	 */
	generate_std_hdr(buff, hdr_len + 1, &hc);

	/*
	 * Message generation : we give a pointer to the next free character of
	 * the log buffer, the remaining buff length and the arguments.
	 */
	generate_std_msg(&buff[hdr_len], buff_len - hdr_len, format, args);
	va_end(args);

	// Write message
	ret = write_msg(p.output_type, log_level, p.output_file, buff);

end:
	free(buff);
	return ret;
}

yall_error yall_call_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function_name,
	const char *filename,
	int32_t line,
	void (*formatter)(yall_call_data *d, const void *args),
	const void *args)
{
	yall_error ret = YALL_SUCCESS;
	char *buff = NULL;
	size_t hdr_len = 0;
	size_t buff_len = 0;
	struct yall_call_data d = { 0 };
	struct header_content hc = { 0 };
	struct yall_subsystem_params p = { 0 };

	if (! initialized) {
		ret = YALL_NOT_INIT;
		goto end;
	}

	get_subsystem(subsystem, &p);

	if (p.status == yall_subsys_disable) {
		ret = YALL_SUBSYS_DISABLED;
		goto end;
	}

	if (log_level < p.log_level) {
		ret = YALL_LOG_LEVEL_TOO_LOW;
		goto end;
	}

	init_call_data(&d);

	/*
	 * Detailled informations about the following calls can be found inside
	 * the sources of yall_log() function.
	 */

	formatter(&d, args);

	fill_header_content(&hc, subsystem, log_level, function_name, filename,
		line);

	hdr_len = generate_call_hdr(NULL, 0, &hc);
	buff_len = hdr_len + d.message_size + 1;

	buff = malloc(buff_len);

	generate_call_hdr(buff, hdr_len + 1, &hc);
	generate_call_msg(&buff[hdr_len], buff_len - hdr_len, &d);

	ret = write_msg(p.output_type, log_level, p.output_file, buff);

end:
	free(buff);
	return ret;
}

yall_error yall_set_subsystem(const char *name,
	const char *parent,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file)
{
	yall_error ret = YALL_SUCCESS;

	if (! initialized) {
		ret = YALL_NOT_INIT;
		goto end;
	}

	if (! name) {
		ret = YALL_NO_NAME;
		goto end;
	}

	struct yall_subsystem *s = remove_subsystem(name);

	if (! s) {
		s = create_subsystem(name, log_level, output_type, output_file);

		if (! s) {
			ret = YALL_CANT_CREATE_SUBSYS;
			goto end;
		}
	} else {
		update_subsystem(s, log_level, output_type, output_file);
	}

	add_subsystem(parent, s);

end:
	return ret;
}

yall_error yall_close(void)
{
	yall_error ret = YALL_SUCCESS;

	if (! initialized) {
		ret = YALL_NOT_INIT;
		goto end;
	}

	if (initialized == 1) {
		_YALL_DBG_INFO("Close library.");
		yall_disable_debug();
		writer_close();
		free_subsystems();
		config_clean();
		initialized = 0;
	} else {
		--initialized;
	}

end:
	return ret;
}

void yall_close_all(void)
{
	for ( ; yall_close() != YALL_NOT_INIT ; )
		;
}
