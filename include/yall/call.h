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

#ifndef _YALL_CALL_H
#define _YALL_CALL_H

#include <stdint.h>
#include <stddef.h>

#include "yall/utils.h"

#define DEFAULT_LINE_SIZE       1024

struct yall_call_data_line {
	char *content;
	struct yall_call_data_line *next;
};

typedef struct yall_call_data {
	uint16_t message_size;
	char *header;
	struct yall_call_data_line *lines;
} yall_call_data;

/*
 * init_call_data : from a yall_call_data pointer, message_size is set to 1
 *  and header contains "\n". The <d> pointer can't be NULL.
 */
void init_call_data(struct yall_call_data *d);

/*
 * add_line : add the given <content> to a new line of the data <d>.
 *      <d> and <content> can't be NULL.
 */
void add_line(struct yall_call_data *d, char *content);

/*
 * remove_first_line : remove and return the first line of the given data <d>.
 */
struct yall_call_data_line *remove_first_line(struct yall_call_data *d);

/*
 * call_data_to_buffer : fill the <buffer> of size <len> with the data of <d>.
 *      None of theses pointers can be NULL.
 */
void convert_data_to_message(char *buffer, size_t len,
	struct yall_call_data *d);

/*
 * yall_call_set_header : called by the user's formatter function, it allow to
 *      define the header of the log message. This header will be added just
 *      after the standard info header (with subsystem name, date, ...).
 *      Both <d> and <format> parameters can't be NULL.
 */
_YALL_PUBLIC void yall_call_set_header(
	yall_call_data *d,
	const char *format,
	...);

/*
 * yall_call_add_line : called by the user's formatter function, it allow to
 *      add a line to the custom message. <indent> is the number of time plus
 *      one that '\t' will be added before the message. <d> and <format> can't
 *      be NULL.
 */
_YALL_PUBLIC void yall_call_add_line(
	yall_call_data *d,
	uint8_t indent,
	const char *format, ...);

#endif
