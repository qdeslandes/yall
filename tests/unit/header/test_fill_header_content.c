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

#include "header/test.h"

/*
 * O.K.
 */
Test(header, test_fill_header_content0)
{
	const char *subsystem = "subsystem";
	const char *function = "test_fill_header_content0";
	const char *filename = "main.c";

	struct header_content hc = { 0 };

	fill_header_content(&hc, subsystem, yall_notice, function, filename, 32);

	cr_assert_str_eq(hc.subsystem, "subsystem");
	cr_assert_str_eq(hc.log_level, "NOTICE");
	cr_assert_str_eq(hc.function_name, "test_fill_header_content0");
	cr_assert_str_eq(hc.filename, "main.c");
	cr_assert_str_eq(hc.line, "32");
}

/*
 * O.K.
 * Line number too long
 */
Test(header, test_fill_header_content1)
{
	const char *subsystem = "subsystem";
	const char *function = "test_fill_header_content0";
	const char *filename = "main.c";

	struct header_content hc = { 0 };

	fill_header_content(&hc, subsystem, yall_notice, function, filename, 1212121212);

	cr_assert_str_eq(hc.subsystem, "subsystem");
	cr_assert_str_eq(hc.log_level, "NOTICE");
	cr_assert_str_eq(hc.function_name, "test_fill_header_content0");
	cr_assert_str_eq(hc.filename, "main.c");
	cr_assert_str_eq(hc.line, "1212121");
}
