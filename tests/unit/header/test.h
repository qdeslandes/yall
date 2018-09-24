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

#ifndef _TEST_HEADER_H
#define _TEST_HEADER_H

#include "yall_test.h"

#include <stdbool.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <jansson.h>

#include "yall/header.h"

#define MATCHES_SIZE	10
#define NBR_MODIFIERS	7

extern enum yall_matches std_matches[MATCHES_SIZE];
extern enum yall_matches call_matches[MATCHES_SIZE];
extern char std_header_format[YALL_HEADER_LEN];
extern char call_header_format[YALL_HEADER_LEN];

extern bool is_modifier(char c, enum yall_matches *match);
extern void set_date(char *buff);
extern void set_matches_and_header(enum header_type hdr_type,
	char **header, enum yall_matches **matches);
extern size_t generate_hdr(enum header_type hdr_type, char *buffer, size_t len,
	struct header_content *hc);

#endif
