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

// TODO : check using this enum outside the library
enum header_type {
	std_header,
	call_header
};

enum yall_matches {
	empty,
	subsystem,
	log_level,
	function,
	filename,
	line,
	date
};

struct header_content {
	const char *subsystem;
	const char *log_level;
	const char *function_name;
	const char *filename;
	char line[YALL_LINE_STR_LEN];
	char date_long[YALL_DATE_LONG_LEN];
};

/*
 * header_compile_format : compile the given format to a printf ready format and
 *	store the modifiers order for proper log message header generation.
 *	<format> can't be NULL.
 */
void header_compile_format(enum header_type hdr_type, char *format);

/*
 * fill_header_content : from a header_content structure, fill the fields with
 *	the given parameters and set the date field.
 *	<hc> can't be NULL.
 */
void fill_header_content(struct header_content *hc, const char *subsystem,
	enum yall_log_level log_level, const char *function_name,
	const char *filename, int32_t line);

/*
 * generate_std_hdr : generate the standard header inside <buffer> with a
 *	maximum length of <len>. The content of <hc> is printed to generate the
 *	header. No memory is allocated of freed. The log level inside <hc>
 *	can't be yall_inherited_level.
 */
size_t generate_std_hdr(char *buffer, size_t len, struct header_content *hc);

/*
 * generate_call_hdr : same prerequisites and constraints as
 *	generate_std_header().
 */
size_t generate_call_hdr(char *buffer, size_t len, struct header_content *hc);

#endif
