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

#include "yall/header.h"

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "yall/error.h"
#include "yall/debug.h"

/*
 * The behaviour of the following code is specific to header generation : the
 * user can define a custom header to change the log level string position,
 * remove the date, ... To generate a correct header from the given format,
 * we define an array which will be used to match the given modifier (%s for
 * a subsystem, %f for the function name, ...) with the proper string during
 * header generation.
 *
 * Define the matches array size means no more than MATCHES_SIZE modifier will
 * be allowed inside the header format string.
 *
 * The header format length is also limited to YALL_HEADER_LEN, which means the
 * compiled header format can't exceed YALL_HEADER_LEN.
 */
#define MATCHES_SIZE	10
#define NBR_MODIFIERS	7	// The first index returns an empty string

static enum yall_matches std_matches[MATCHES_SIZE] = { 0 };
static enum yall_matches call_matches[MATCHES_SIZE] = { 0 };
static char std_header_format[YALL_HEADER_LEN] = { 0 };
static char call_header_format[YALL_HEADER_LEN] = { 0 };

/*
 * is_modifier : returns true is the given character is a yall modifier, false
 *	otherwise. <match> is a pointer to an element of the matches array, it
 *	is used to order the modifier set in the header, and replace them
 *	properly during the header generation.
 */
static inline bool is_modifier(char c, enum yall_matches *match)
{
	switch (c) {
	case 's':
		*match = subsystem;
		break;
	case 'l':
		*match = log_level;
		break;
	case 'f':
		*match = function;
		break;
	case 'F':
		*match = filename;
		break;
	case 'L':
		*match = line;
		break;
	case 'd':
		*match = date;
		break;
	default:
		return false;
	}

	return true;
}

/*
 * set_date : fill the <date> string pointer with the current date time,
 *	formatted in a generic way.
 */
static void set_date(char *date)
{
	struct tm tm;
	time_t t = time(NULL);

	#ifdef __linux__
	localtime_r(&t, &tm);
	#else
	localtime_s(&tm, &t);
	#endif

	snprintf(date, YALL_DATE_LONG_LEN, "%04d-%02d-%02d %02d:%02d:%02d",
		tm.tm_year + 1900,
		tm.tm_mon + 1,
		tm.tm_mday,
		tm.tm_hour,
		tm.tm_min,
		tm.tm_sec);
}

/*
 * set_matches_and_header : from an <header_type>, it match the proper <header>
 *	and <matches> array. This avoid redundant code to manage std_header and
 *	call_header.
 */
static void set_matches_and_header(enum header_type hdr_type,
	char **header, enum yall_matches **matches)
{
	switch (hdr_type) {
	case std_header:
		*matches = std_matches;
		*header = std_header_format;
		break;
	case call_header:
		*matches = call_matches;
		*header = call_header_format;
		break;
	default:
		*matches = std_matches;
		*header = std_header_format;
		break;
	}
}

void header_compile_format(enum header_type hdr_type, char *format)
{
	// TODO : avoid using "int", use more clear type : uint16_t, ...
	// TODO : handle successive "%"

	int hdr_len = 0;
	int match_idx = 0;
	char *hdr = NULL;
	enum yall_matches *matches = NULL;
	bool seek_modifier = false;
	bool allow_modifier = true;

	set_matches_and_header(hdr_type, &hdr, &matches);

	memset(matches, 0, MATCHES_SIZE);

	for ( ; *format && hdr_len < YALL_HEADER_LEN-1; ++format, ++hdr_len) {
		if (*format == '%')
			seek_modifier = true;

		if (seek_modifier && allow_modifier && is_modifier(*format,
			&matches[match_idx])) {
			++match_idx;
			*hdr++ = 's';

			if (match_idx > MATCHES_SIZE) {
				_YALL_DBG_ERR(
					"The header modifiers array is full.");
				allow_modifier = false;
			}

			seek_modifier = false;
		} else {
			*hdr++ = *format;
		}
	}

	*hdr = '\0';
}

void fill_header_content(struct header_content *hc, const char *subsystem,
	enum yall_log_level log_level, const char *function_name,
	const char *filename, int32_t line)
{
	hc->subsystem = subsystem;
	hc->log_level = get_log_level_name(log_level);
	hc->function_name = function_name;
	hc->filename = filename;

	snprintf(hc->line, YALL_LINE_STR_LEN, "%d", line);
	set_date(hc->date_long);
}

/*
 * generate_hdr : main function handling the header generation, the header
 *	format used depend of <hdr_type>. <buffer> will store the generated
 *	header, it won't write more than <len> (including the nul terminating
 *	character). <hc> can't be NULL.
 *	This function can be used as snprintf and friends, as if <len> is equals
 *	to 0, the number of characters that SHOULD HAVE been wrote will be
 *	returned.
 */
static size_t generate_hdr(enum header_type hdr_type, char *buffer, size_t len,
	struct header_content *hc)
{
	size_t wrote = 0;
	char *hdr = NULL;
	enum yall_matches *matches = NULL;

	set_matches_and_header(hdr_type, &hdr, &matches);

	const char *ordered_content[NBR_MODIFIERS] = {
		"",
		hc->subsystem,
		hc->log_level,
		hc->function_name,
		hc->filename,
		hc->line,
		hc->date_long
	};

	// TODO : the way the header is printed is ABSOLUTELY BARBARIC
	wrote = snprintf(buffer, len, hdr, ordered_content[matches[0]],
		ordered_content[matches[1]], ordered_content[matches[2]],
		ordered_content[matches[3]], ordered_content[matches[4]],
		ordered_content[matches[5]], ordered_content[matches[6]],
		ordered_content[matches[7]], ordered_content[matches[8]],
		ordered_content[matches[9]]);

	return wrote;
}

size_t generate_std_hdr(char *buffer, size_t len, struct header_content *hc)
{
	return generate_hdr(std_header, buffer, len, hc);
}

size_t generate_call_hdr(char *buffer, size_t len, struct header_content *hc)
{
	return generate_hdr(call_header, buffer, len, hc);
}
