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

#define DEFAULT_LINE_SIZE       1024U

/**
 * \struct yall_call_data_line
 * \brief Represent a line during a call to a macro YALL_CALL_xxx.
 * \var yall_call_data_line::content
 *	\brief Content of the line : nul-terminated string to be wrote on the
 *	output medium.
 * \var yall_call_data_line::next
 *	\brief Next element of the lines list.
 */
struct yall_call_data_line {
	char *content;
	struct yall_call_data_line *next;
};

/**
 * \struct yall_call_data
 * \brief Structure storing calling system data. An instance of this structure
 *	is passed as a parameter to the formatter function during calls to
 *	YALL_CALL_xxx macros. All these values shouldn't be modified by the
 *	formatter.
 * \var yall_call_data::message_size
 *	\brief Total length of the message, including header.
 * \var yall_call_data::header
 *	\brief Header of the log message : line of text placed juste after the
 *	yall's formatted log header.
 * \var yall_call_data::lines
 *	\brief List of lines.
 */
typedef struct yall_call_data {
	size_t message_size;
	char *header;
	struct yall_call_data_line *lines;
} yall_call_data;

/**
 * \brief Initialize a structure yall_call_data by setting header to "\n" and
 *	message_size to 1.
 * \param d Pointer to structure of type yall_call_data. Can't be NULL.
 */
void init_call_data(struct yall_call_data *d);

/**
 * \brief Add a line to the structure yall_call_data with the given content.
 * \param d Pointer to structure of type yall_call_data. Can't be NULL.
 * \param content Nul-terminated string to add as a line on the final log
 *	message can't be NULL.
 */
void add_line(struct yall_call_data *d, char *content);

/**
 * \brief Remove and return the first line of the given yall_call_data.
 * \param d Pointer to structure of type yall_call_data. Can't be NULL.
 * \return First line of the given yall_call_data.
 */
struct yall_call_data_line *remove_first_line(struct yall_call_data *d);

/**
 * \brief Convert the content of the structure yall_call_data to a
 *	nul-terminated string inside *buffer* parameter. Limited to *len* bytes.
 * \param buffer Buffer to write the log message in.
 * \param len Maximum length of characters to write inside *buffer* including
 *	nul-terminating '\0'.
 * \param d Pointer to structure of type yall_call_data. Can't be NULL.
 */
void convert_data_to_message(char *buffer, size_t len,
	struct yall_call_data *d);

/**
 * \brief Called by the user's formatter function, it allow to define the header
 *	of the log message. This header will be added just after the standard
 *	info header (with subsystem name, date, ...).
 * \param d Pointer to structure of type yall_call_data. Can't be NULL.
 * \param format Printf like format. All printf's modifiers are allowed. Can't
 *	be NULL.
 * \param ... Variadic parameters for the format.
 */
_YALL_PUBLIC void yall_call_set_header(
	yall_call_data *d,
	const char *format,
	...);

/**
 * \brief Called by the user's formatter function, it allow to add a line to the
 *	custom message.
 * \param d Pointer to structure of type yall_call_data. Can't be NULL.
 * \param indent Number of tabulations to add before adding this line on the
 *	final log message. This is used to display prettier log messages.
 * \param format Printf like format. All printf's modifiers are allowed. Can't
 *	be NULL.
 * \param ... Variadic parameters for the format.
 */
_YALL_PUBLIC void yall_call_add_line(
	yall_call_data *d,
	uint8_t indent,
	const char *format, ...);

#endif
