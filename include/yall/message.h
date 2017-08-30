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

#ifndef _YALL_MESSAGE_H
#define _YALL_MESSAGE_H

#include <stdint.h>
#include <stdarg.h>

#include "yall/header.h"
#include "yall/call.h"
#include "yall/log_levels.h"
#include "yall/output_types.h"

#define YALL_MSG_LEN	512
#define MSG_HEADER_LEN	77
#define FUNC_NAME_LEN	17

/*
 * struct message : this structure is used to store the content of a log
 *	message, like the log level, the message itself, the output type, and
 *	many other useful data. It will be pushed to the messages queue.
 */
struct message {
	char *data;
	enum yall_log_level log_level;
	enum yall_output_type output_type;
	const char *output_file;
};

/*
 * message_new : craete and return a new message with the given parameters.
 *	This message must be freed with the proper function as internals must
 *	be handled specifically. <data> and <output_file> can be NULL. It is
 *	useless to test the return value, as it use malloc. If malloc fail,
 *	your first problem won't be the NULL returning function.
 */
struct message *message_new(char *data,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file);

/*
 * message_delete : delete a given message. <msg> can't be NULL.
 */
void message_delete(struct message *msg);

/*
 * generate_message : create the log message. It fills <buffer> we given data
 *	and specific format. No pointer argument can be NULL, but <args> can be
 *	empty.
 *	Returns the number of characters wrote. It works the same way as
 *	snprintf and friends as if <len> equals 0, it returns the number of
 *	characters than would have been wrote.
 */
size_t generate_std_msg(char *log_buffer, size_t len,
	const char *message_format, va_list args);

/*
 * generate_call_msg : create the log message from the call data. The call_data
 *	are freed after use.
 *	<buffer> and <d> can't be NULL.
 */
void generate_call_msg(char *buffer, size_t len, struct yall_call_data *d);

#endif
