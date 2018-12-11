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
#include "yall/subsystem.h"
#include "yall/log_level.h"
#include "yall/output/types.h"
#include "yall/output/file.h"
#include "yall/output/console.h"

#define YALL_MSG_LEN	512
#define MSG_HEADER_LEN	77
#define FUNC_NAME_LEN	17

/**
 * \struct message
 * \brief This is a message. It contains a log line and its output parameters
 *	(gathered from the proper subsystem). This structure is used to store
 *	the different log messages inside a lockless queue, waiting to be wrote
 *	on the medium. It should be avoided to create a message manually, use
 *	message_new() instead.
 * \var message::data
 *	\brief Log message to write.
 * \var message::log_level
 *	\brief Log level to use when writing the message.
 * \var message::output_type
 *	\brief Output type to use when writing the message.
 * \var message::console
 *	\brief Console output type parameters.
 * \var message::file
 *	\brief File output type parameters.
 */
struct message {
	char *data;
	enum yall_log_level log_level;
	enum yall_output_type output_type;
	struct yall_console_output_config console;
	struct yall_file_output_config file;
};

/**
 * \brief Create and returns a new message with the given parameters. This
 *	message must be freed with the proper function as internals must be
 *	handled specifically. It is useless to test the return value, as it use
 *	malloc. If malloc fail, your first problem won't be the NULL returning
 *	function.
 * \param data Data to set inside the message. This value can be NULL.
 * \param log_level Log level of the message.
 * \param p Parameters used to write the log message. It is used to copy
 *	the different configuration parameters.
 */
struct message *message_new(char *data,
	enum yall_log_level log_level,
	struct yall_subsystem_params *p);

/**
 * \brief Delete the given message. Free the data too.
 * \param msg Message to delete. Can't be NULL.
 */
void message_delete(struct message *msg);

/**
 * \brief Create the log message. It fills *buffer* we given data and specific
 *	format. By the way, the function returns the required buffer size of the
 *	length parameter is 0, by it does not add room for '\n' and '\0'.
 * \param log_buffer Buffer in which the log message will be wrote.
 * \param len Length of the log buffer.
 * \param message_format Format to use when generating the log message.
 * \param args Arguments to use with the message's format. Can be empty.
 * \return Returns the number of characters wrote. It works the same way as
 *	snprintf and friends as if *len* equals 0, it returns the number of
 *	characters than would have been wrote.
 */
size_t generate_std_msg(char *log_buffer, size_t len,
	const char *message_format, va_list args);

/**
 * \brief Create the log message from the call data. The call_data are freed
 *	after use.
 * \param buffer Buffer in which log message will be wrote.
 * \param len Length of the log buffer.
 * \param d Call data to generate the log message from.
 */
void generate_call_msg(char *buff, size_t len, struct yall_call_data *d);

#endif
