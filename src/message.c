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

#include "yall/message.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "yall/utils.h"
#include "yall/errors.h"
#include "yall/subsystem.h"

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

	int ret = snprintf(buffer, YALL_MSG_LEN, "%-*.*s ::: %-9s :: %s :: %04d-%02d-%02d %02d:%02d:%02d : ",
		SUBSYS_NAME_LEN,
		SUBSYS_NAME_LEN,
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
