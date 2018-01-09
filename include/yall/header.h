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

#ifndef _YALL_HEADER_H
#define _YALL_HEADER_H

#include <stdint.h>
#include <stddef.h>

#include "yall/log_level.h"

#define YALL_HEADER_LEN		64
#define YALL_DATE_LONG_LEN	20
#define YALL_LINE_STR_LEN	8

/**
 * \enum header_type
 * \brief Enumerator used to store the kind of header used.
 * \var header_type::std_header
 *	\brief This header type is used for the standard log message, which
 *	is used defaultly.
 * \var header_type::call_header
 *	\brief This header type is used when calling a formatting function
 *	through a YALL_CALL_xxx function.
 */
enum header_type {
	std_header,
	call_header
};

/**
 * \enum yall_matches
 * \brief Enumerator used when matching format parameter to the corresponding
 *	values, inside an array.
 */
enum yall_matches {
	match_empty,
	match_subsystem,
	match_log_level,
	match_function,
	match_filename,
	match_line,
	match_date
};

/**
 * \struct header_content
 * \brief Structure representing all the possible data that can be write inside
 *	a log message header. The header generation function can then get the
 *	header values from it.
 * \var header_content::subsystem
 *	\brief Name of the subsystem as a nul-terminated string.
 * \var header_content::log_level
 *	\brief Log level of the message as a nul-terminated string.
 * \var header_content::function_name
 *	\brief Name of the function sending the log message as a
 *	nul-terminated string.
 * \var header_content::filename
 *	\brief Name of the file where the log sending function is located, as
 *	a nul-terminated string.
 * \var header_content::line 
 *	\brief Number of the line calling the log function. Can't be longer than
 *	YALL_LINE_STR_LEN.
 * \var header_content::date_long
 *	\brief Date of the log message, as a nul-terminated string. Can't be
 *	longer than YALL_DATE_LONG_LEN.
 */
struct header_content {
	const char *subsystem;
	const char *log_level;
	const char *function_name;
	const char *filename;
	char line[YALL_LINE_STR_LEN];
	char date_long[YALL_DATE_LONG_LEN];
};

/**
 * \brief Compile the given format to a printf ready format and store the
 *	modifiers order for proper log message header generation.
 * \param hdr_type Header type is a value of type enum header_type. It is used
 *	to match the given format to the proper matches array.
 * \param format Format to process. It can contains all the printf modifiers and
 *	all the yall modifiers available in is_modifier(). Can't be NULL.
 */
void header_compile_format(enum header_type hdr_type, const char *format);

/**
 * \brief From a structure header_content, fill the fields with the given
 *	parameters and set the date field.
 * \param hc Header content structure to be filled. Can't be NULL.
 * \param subsystem Subsystem name.
 * \param log_level Log level as an enum yall_log_level.
 * \param function_name Name of the calling function.
 * \param filename Name of the file of the calling function.
 * \param line Line of the call.
 */
void fill_header_content(struct header_content *hc, const char *subsystem,
	enum yall_log_level log_level, const char *function_name,
	const char *filename, int32_t line);

/**
 * \brief Generate the standard header with the struct header_content
 *	parameters. No memory is allocated or freed. The header_content
 *	structure should not contains any inherited value.
 * \param buffer Buffer used to store the generated standard header.
 * \param len Maximum length of the buffer, including nul terminating character.
 * \param hc Struture header_content storing the data to write on the buffer.
 */
size_t generate_std_hdr(char *buffer, size_t len, struct header_content *hc);

/**
 * \brief Generate the call header with the struct header_content parameters.
 *	No memory is allocated or freed. The header_content structure should not
 *	contains any inherited value.
 * \param buffer Buffer used to store the generated standard header.
 * \param len Maximum length of the buffer, including nul terminating character.
 * \param hc Struture header_content storing the data to write on the buffer.
 */
size_t generate_call_hdr(char *buffer, size_t len, struct header_content *hc);

#endif
