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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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

#include "yall/utils.h"
#include "yall/errors.h"
#include "yall/writer.h"
#include "yall/message.h"
#include "yall/subsystem.h"
#include "yall/debug.h"

#include "version.h"
#define YALL_VERSION_STR STRINGIFY(YALL_MAJOR) "." STRINGIFY(YALL_MINOR) "." STRINGIFY(YALL_PATCH)

static uint32_t version = (YALL_MAJOR << 16) | (YALL_MINOR << 8) | YALL_PATCH;
static const char *version_string = "yall, Quentin <Naccyde> Deslandes, version " YALL_VERSION_STR;

uint32_t yall_get_version(void)
{
	return version;
}

const char *yall_get_version_string(void)
{
	return version_string;
}

static bool initialized = false;

uint8_t yall_init(void)
{
	uint8_t ret = YALL_OK;

	if (initialized) {
		ret = YALL_ALREADY_INIT;
		goto err;
	}

	initialized = true;

	if ((ret = writer_init()))
		goto err;

	return ret;

err:
	initialized = false;
	return ret;
}

uint8_t yall_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function,
	const char *format,
	...)
{
	uint8_t ret = YALL_OK;

	char *msg = NULL;
	struct yall_subsystem *s = NULL;
	struct yall_subsystem_params p = { 0 };

	if (! initialized) {
		ret = YALL_NOT_INIT;
		goto end;
	}

	// Get subsystem and check its status
	s = get_subsystem(subsystem, &p);

	if (! s) {
		ret = YALL_SUBSYS_NOT_EXISTS;
		goto end;
	} else if (p.status == yall_subsys_disable) {
		ret = YALL_SUBSYS_DISABLED;
		goto end;
	}

	if (log_level < p.log_level) {
		ret = YALL_LOG_LEVEL_TOO_LOW;
		goto end;
	}

	// Create message
	if (! (msg = malloc(YALL_MSG_LEN))) {
		ret = YALL_NO_MEM;
		goto end;
	}

	va_list args;
	va_start(args, format);
	generate_message(msg,
		format,
		subsystem,
		log_level,
		function,
		args);
	va_end(args);

	// Write message
	ret = write_msg(p.output_type, log_level, p.output_file, msg);

end:
	free(msg);
	return ret;
}

uint8_t yall_call_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function_name,
	void (*function)(char *buffer, void *args),
	void *args)
{
	uint8_t ret = YALL_OK;

	if (! initialized) {
		ret = YALL_NOT_INIT;
		goto end;
	}

	// Print the header
	if ((ret = yall_log(subsystem, log_level, function_name, "")) != YALL_OK)
		goto end;

	// Call function to create the message and print it
	char msg[YALL_CALL_BUFF_LEN] = { 0 };
	struct yall_subsystem_params p = { 0 };

	// Get subsystem's parameters. This can't fail.
	get_subsystem(subsystem, &p);

	function(msg, args);

	ret = write_msg(p.output_type, log_level, p.output_file, msg);

end:
	return ret;
}

uint8_t yall_set_subsystem(const char *name,
	const char *parent,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file)
{
	uint8_t ret = YALL_OK;

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


uint8_t yall_close(void)
{
	uint8_t ret = YALL_OK;

	if (! initialized) {
		ret = YALL_NOT_INIT;
		goto end;
	}

	initialized = false;

	writer_close();
	free_subsystems();

end:
	return ret;
}
