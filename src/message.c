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

#include "yall/message.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "yall/utils.h"
#include "yall/errors.h"

static char *log_levels_names[8] = {
		"DEBUG",
		"INFO",
		"NOTICE",
		"WARNING",
		"ERROR",
		"CRITICAL",
		"ALERT",
		"EMERGENCY"
	};

/*
 * generate_header : function in charge to generate the message header. A char
 * 	array is passed to be filled by the parameters and the date. Once done,
 * 	the status is returned. All pointer can't be NULL and the value
 * 	<log_level> can't be equal to yall_inherited_level.
 */
static uint8_t generate_header(char *buffer,
	const char *subsystem,
	enum yall_log_level log_level,
	const char *function)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	int ret = snprintf(buffer, YALL_MSG_LEN, "%s ::: %-9s :: %s :: %04d-%02d-%02d %02d:%02d:%02d : ",
		subsystem,
		log_levels_names[log_level],
		function,
		tm.tm_year + 1900,
		tm.tm_mon + 1,
		tm.tm_mday,
		tm.tm_hour,
		tm.tm_min,
		tm.tm_sec);

	return ret >= 0 ? YALL_OK : YALL_STRING_WRITE_ERR;
}

/*
 * generate_message : create the log message. It fills <buffer> we given data
 * 	and specific format. No pointer argument can be NULL, but <args> can be
 * 	empty.
 */
uint8_t generate_message(char *buffer,
	const char *format,
	const char *subsystem,
	enum yall_log_level log_level,
	const char *function,
	va_list args)
{
	uint8_t ret = YALL_OK;

	ret = generate_header(buffer, subsystem, log_level, function);
	if (ret != YALL_OK)
		goto end;

	size_t len = strlen(buffer);
	if (vsnprintf(&buffer[len], YALL_MSG_LEN - len, format, args) < 0)
		ret = YALL_STRING_WRITE_ERR;

	len = strlen(buffer);
	if (len == YALL_MSG_LEN - 1)
		--len;

	buffer[len] = '\n';
	buffer[len+1] = '\0';

end:
	return ret;
}
