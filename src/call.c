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

#include "yall/call.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "yall/config/parameters.h"

yall_call_data *call_new(void)
{
	yall_call_data *d = malloc(sizeof(yall_call_data));

	d->message_size = 0;
	d->header = NULL;
	d->lines = NULL;

	return d;
}

void call_delete(yall_call_data *d)
{
	struct yall_call_data_line *l = NULL;

	while ((l = remove_first_line(d))) {
		free(l->content);
		free(l);
	}

	free(d->header);
	free(d);
}

size_t call_get_buffer_length(yall_call_data *d)
{
	size_t len = 0;
	size_t nb_lines = 0;
	struct yall_call_data_line *l = d->lines;

	len = d->message_size;
	len += 2; // '\0' && header's '\n'

	while (l) {
		++nb_lines;
		l = l->next;
	}

	len += nb_lines;

	return len;
}

void add_line(struct yall_call_data *d, char *content)
{
	struct yall_call_data_line *l = NULL;

	l = malloc(sizeof(struct yall_call_data_line));

	if (d->lines == NULL) {
		d->lines = l;
	} else {
		struct yall_call_data_line *tmp = d->lines;

		for ( ; tmp->next; tmp = tmp->next)
			;
		tmp->next = l;
	}

	l->content = content;
	l->next = NULL;
}

struct yall_call_data_line *remove_first_line(struct yall_call_data *d)
{
	struct yall_call_data_line *l = d->lines;

	if (l) {
		d->lines = l->next;
		d->message_size -= strlen(l->content);
	}

	return l;
}

void yall_call_set_header(yall_call_data *d, const char *format, ...)
{
	va_list args;
	va_list args_cpy;
	size_t len = 0;

	va_copy(args_cpy, args);

	if (d->header) {
		d->message_size -= strlen(d->header);
		free(d->header);
	}

	// Compute buffer size
	va_start(args_cpy, format);
	len = (size_t)vsnprintf(NULL, 0, format, args_cpy);
	va_end(args_cpy);

	d->header = malloc(len + 1);

	// Write string in buffer
	va_start(args, format);
	vsprintf(d->header, format, args);
	va_end(args);

	d->message_size += len;
}

void yall_call_add_line(yall_call_data *d, uint8_t indent, const char *format,
	...)
{
	va_list args;
	va_list args_cpy;
	size_t i = 0;
	size_t len = 0;
	char *content = NULL;
	uint8_t tab_width = yall_config_get_tab_width();

	++indent; // Default to 1 tab for call messages
	va_copy(args_cpy, args);

	// Compute buffer size
	va_start(args_cpy, format);
	len = (size_t)vsnprintf(NULL, 0U, format, args_cpy) +
		(size_t)tab_width * indent;
	va_end(args_cpy);

	content = malloc(len + 1);

	for (i = 0; i < tab_width * indent; ++i)
		content[i] = ' ';

	// Write message in buffer
	va_start(args, format);
	vsprintf(&content[i], format, args);
	va_end(args);

	d->message_size += len;

	add_line(d, content);
}
