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

#include "yall/message.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "yall/utils.h"
#include "yall/error.h"
#include "yall/subsystem.h"
#include "yall/debug.h"
#include "yall/header.h"

struct message *message_new(char *data,
	enum yall_log_level log_level,
	struct yall_subsystem_params *p)
{
	struct message *msg = malloc(sizeof(struct message));

	msg->data = data;
	msg->log_level = log_level;
	msg->output_type = p->output_type;
	msg->file.filename = p->file.filename;

	return msg;
}

void message_delete(struct message *msg)
{
	free(msg->data);
	free(msg);
}

size_t generate_std_msg(char *log_buffer, size_t len,
	const char *message_format, va_list args)
{
	size_t ret = (size_t)vsnprintf(log_buffer, len, message_format, args);

	if (len >= 2)
		log_buffer[len-2] = '\n';

	if (len >= 1)
		log_buffer[len-1] = '\0';

	return ret;
}

void generate_call_msg(char *buffer, size_t len, struct yall_call_data *d)
{
	struct yall_call_data_line *l = NULL;

	snprintf(buffer, len, "%s", d->header);
	free(d->header);

	while ((l = remove_first_line(d))) {
		size_t curr_len = strlen(buffer);

		snprintf(&buffer[curr_len], len - curr_len, l->content);

		/*
		 * TODO : call_data free should be call in the same scope as
		 * it is created.
		 */
		free(l->content);
		free(l);
	}
}
