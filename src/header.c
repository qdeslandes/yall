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

#include "yall/header.h"

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "yall/errors.h"

#define MATCHES_SIZE	10
#define NBR_MODIFIERS	5	// The first index returns an empty string

static int8_t std_matches[MATCHES_SIZE] = { 0 };
static int8_t call_matches[MATCHES_SIZE] = { 0 };
static char std_header_format[YALL_HEADER_LEN] = { 0 };
static char call_header_format[YALL_HEADER_LEN] = { 0 };

/*
 * Modifiers order:
 * 	BUT MATCHES[0] contains an empty content to print
 * 	subsystem
 * 	log_level
 * 	function
 * 	date
 * 	message
 */

// TODO : header format size is hardcoded
// TODO : matches size is hardcoded
// TODO : prevent : this function is not thread safe
// TODO : handle successive tokens
// TODO : if token is null (with "" as string)
// TODO : format can be modified by strtok
// TODO : replacement size is hardcoded
// Get modifier, convert it to "replacement" with the proper parameters

	/*
	clock_t start;
	bool init = false;
	if (! init) {
		start = clock();
		init = true;
	}*/

bool is_modifier(char c, int8_t *match)
{
	switch (c) {
	case 's':
		*match = 1;
		break;
	case 'l':
		*match = 2;
		break;
	case 'f':
		*match = 3;
		break;
	case 'd':
		*match = 4;
		break;
	default:
		return false;
		break;
	}

	return true;
}

void header_compile_format(enum header_type hdr_type, char *format)
{
	int header_size = 0;
	int match_idx = 0;
	bool seek_modifier = false;
	char *header = NULL;
	int8_t *matches = NULL;

	switch (hdr_type) {
	case std_header:
		matches = std_matches;
		header = std_header_format;
		break;
	case call_header:
		matches = call_matches;
		header = call_header_format;
		break;
	default:
		matches = std_matches;
		header = std_header_format;
		break;
	}

	memset(matches, 0, MATCHES_SIZE);

	for ( ; *format && header_size < YALL_HEADER_LEN-1; ++format, ++header_size) {
		if (*format == '%')
			seek_modifier = true;

		if (is_modifier(*format, &matches[match_idx])) {
			++match_idx;
			*header++ = 's';
		} else {
			*header++ = *format;
		}
	}

	*header = '\0';
}

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

void fill_header_content(struct header_content *hc, const char *subsystem, enum yall_log_level log_level, const char *function_name)
{
	hc->subsystem = subsystem;
	hc->log_level = get_log_level_name(log_level);
	hc->function_name = function_name;

	set_date(hc->date_long);
}

/*
 * generate_header : function in charge to generate the message header. A char
 *      array is passed to be filled by the parameters and the date. Once done,
 *      the status is returned. All pointer can't be NULL and the value
 *      <log_level> can't be equal to yall_inherited_level.
 *      If the function's name trimming fail, the function's name is not
 *      printed inside the header, but no error is shown. TODO : Fix it ?
 */
static size_t generate_header(enum header_type hdr_type, size_t len, char *buffer, struct header_content *hc)
{
	char *header_format = NULL;
	int8_t *matches = NULL;

	switch (hdr_type) {
	case std_header:
		matches = std_matches;
		header_format = std_header_format;
		break;
	case call_header:
		matches = call_matches;
		header_format = call_header_format;
		break;
	default:
		matches = std_matches;
		header_format = std_header_format;
		break;
	}

	// TODO : the way the header is printed is ABSOLUTELY BARBARIC
	const char *ordered_content[NBR_MODIFIERS] = {
		"",
		hc->subsystem,
		hc->log_level,
		hc->function_name,
		hc->date_long
	};

        size_t wrote = snprintf(buffer, len, header_format,
		ordered_content[matches[0]],
		ordered_content[matches[1]],
		ordered_content[matches[2]],
		ordered_content[matches[3]],
		ordered_content[matches[4]],
		ordered_content[matches[5]],
		ordered_content[matches[6]],
		ordered_content[matches[7]],
		ordered_content[matches[8]],
		ordered_content[matches[9]]
	);

        return wrote;
}

size_t generate_std_header(char *buffer, size_t len, struct header_content *hc)
{
	generate_header(std_header, len, buffer, hc);
}

size_t generate_call_header(char *buffer, size_t len, struct header_content *hc)
{
	generate_header(call_header, len, buffer, hc);
}