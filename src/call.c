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

#include "yall/call.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "yall/config.h"

// TODO : remove the limited line length

void init_call_data(struct yall_call_data *d)
{
	d->message_size = 1;

	d->header = malloc(DEFAULT_LINE_SIZE);
	d->header[0] = '\n';
	d->header[1] = 0;
}

void add_line(struct yall_call_data *d, char *content)
{
        struct yall_call_data_line *l = malloc(sizeof(struct yall_call_data_line));

        if (d->lines == NULL) {
                d->lines = l;
        } else {
                struct yall_call_data_line *tmp = d->lines;
                for ( ; tmp->next; tmp = tmp->next) ;
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

void convert_data_to_message(char *buffer, size_t len, struct yall_call_data *d)
{
        snprintf(buffer, len, "%s", d->header);
        free(d->header);

        struct yall_call_data_line *l = NULL;
        while ((l = remove_first_line(d))) {
                size_t curr_len = strlen(buffer);
                snprintf(&buffer[curr_len], len - curr_len, l->content);

                free(l->content);
                free(l);
        }
}

void yall_call_set_header(yall_call_data *d, const char *format, ...)
{
        if (d->header)
                d->message_size -= strlen(d->header);

        // Create the proper format with \n
        char *_format = malloc(strlen(format) + 2);
        snprintf(_format, strlen(format) + 2, "%s%c", format, '\n');

        va_list args;
        va_start(args, format);

        vsnprintf(d->header, DEFAULT_LINE_SIZE, _format, args);
        d->message_size += strlen(d->header);

        va_end(args);

        free(_format);
}

void yall_call_add_line(yall_call_data *d, uint8_t indent, const char *format, ...)
{
        ++indent; // To, defaultly, set all line at 1 tab

        char *line_content = malloc(DEFAULT_LINE_SIZE);

	uint8_t i = 0;
	uint8_t tab_width = yall_config_get_tab_width();
        for ( ; i < tab_width * indent; ++i)
		line_content[i] = ' ';

        // Create the message line
        va_list args;
        va_start(args, format);

        vsnprintf(&line_content[i], DEFAULT_LINE_SIZE - tab_width * indent, format, args);

        va_end(args);

        // Manage \n
        size_t lf = strlen(line_content) == DEFAULT_LINE_SIZE - 1 ?
                DEFAULT_LINE_SIZE - 2 : strlen(line_content);

        line_content[lf] = '\n';
        line_content[lf+1] = '\0';

        // Add the line to the data list
        add_line(d, line_content);
        d->message_size += strlen(line_content);
}
