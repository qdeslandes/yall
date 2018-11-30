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

struct yall_call_data *call_data_new(void)
{
	struct yall_call_data *d = malloc(sizeof(struct yall_call_data));

	d->message_size = 1;

	// TODO: allocate header here or on demand ?
	d->header = malloc(DEFAULT_LINE_SIZE);
	d->header[0] = '\n';
	d->header[1] = '\0';

	d->lines = ll_new();

	return d;
}

void call_data_delete(struct yall_call_data *d)
{
	ll_delete(d->lines, &free);
	// TODO: header should be freed here
	//free(d->header);
	free(d);
}

void yall_call_set_header(yall_call_data *d, const char *format, ...)
{
	va_list args;
	// Create the proper format with \n
	char *_format = malloc(strlen(format) + 2);

	if (d->header)
		d->message_size -= strlen(d->header);

	snprintf(_format, strlen(format) + 2, "%s%c", format, '\n');

	va_start(args, format);

	vsnprintf(d->header, DEFAULT_LINE_SIZE, _format, args);
	d->message_size += strlen(d->header);

	va_end(args);

	free(_format);
}

void yall_call_add_line(yall_call_data *d, uint8_t indent, const char *format,
	...)
{
	va_list args = {{0}};
	uint8_t i = 0;
	uint8_t tab_width = yall_config_get_tab_width();
	char *line_content = malloc(DEFAULT_LINE_SIZE);

	++indent; // To, defaultly, set all line at 1 tab

	for ( ; i < tab_width * indent; ++i)
		line_content[i] = ' ';

	// Create the message line
	va_start(args, format);
	vsnprintf(&line_content[i], DEFAULT_LINE_SIZE -
		(uint32_t)(tab_width * indent), format, args);
	va_end(args);

	// Manage \n
	size_t lf = strlen(line_content) == DEFAULT_LINE_SIZE - 1 ?
		DEFAULT_LINE_SIZE - 2 : strlen(line_content);

	line_content[lf] = '\n';
	line_content[lf+1] = '\0';

	// Add the line to the data list
	ll_insert_last(d->lines, line_content);
	d->message_size += strlen(line_content);
}
