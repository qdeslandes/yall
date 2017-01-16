/*
 * Copyright (C) 2017, by Quentin Deslandes
 *
 * This file is part of yall.
 *
 * yall is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * yall is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with yall.  If not, see <http://www.gnu.org/licenses/>.
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

static bool initialized = false;

uint8_t yall_init(void)
{
	uint8_t ret = YALL_OK;

	if (initialized) {
		ret = YALL_ALREADY_INIT;
		goto end;
	}

	initialized = true;

	if ((ret = writer_init()))
		goto end;

end:
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
	struct yall_subsystem_params p = { 0 };

	// Get subsystem
	if (! get_subsystem(subsystem, &p)) {
		ret = YALL_SUBSYS_NOT_EXISTS;
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
	ret = generate_message(msg,
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

	// Print the header
	if ((ret = yall_log(subsystem, log_level, function_name, "")) != YALL_OK)
		goto end;

	// Call function to create the message and print it
	char msg[YALL_CALL_BUFF_LEN] = { 0 };
	struct yall_subsystem_params p = { 0 };

	// Get subsystem
	if (! get_subsystem(subsystem, &p)) {
		ret = YALL_SUBSYS_NOT_EXISTS;
		goto end;
	}

	if (log_level < p.log_level) {
		ret = YALL_LOG_LEVEL_TOO_LOW;
		goto end;
	}

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

	if (! name) {
		ret = YALL_NO_NAME;
		goto end;
	}

	struct yall_subsystem *s = remove_subsystem(name);

	if (! s)
		s = create_subsystem(name, log_level, output_type, output_file);
	else
		update_subsystem(s, log_level, output_type, output_file);

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
