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

#ifndef _YALL_MESSAGE_H
#define _YALL_MESSAGE_H

#include <stdint.h>
#include <stdarg.h>

#include "yall/log_levels.h"

#define YALL_MSG_LEN	        512
#define MSG_HEADER_LEN          77
#define FUNC_NAME_LEN		17

/*
 * generate_header : function in charge to generate the message header. A char
 * 	array is passed to be filled by the parameters and the date. Once done,
 * 	the status is returned. All pointer can't be NULL and the value
 * 	<log_level> can't be equal to yall_inherited_level.
 * 	If the function's name trimming fail, the function's name is not
 * 	printed inside the header, but no error is shown. TODO : Fix it ?
 */
uint8_t generate_header(char *buffer,
	const char *subsystem,
	enum yall_log_level log_level,
	const char *function);

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
	va_list args);

#endif
