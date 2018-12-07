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

#include "message/test.h"

/*
 * O.K.
 * Len equals 0
 */
Test(message, test_generate_call_message0)
{
	char buffer[64] = { 0 };
	yall_call_data *d = call_new();

	yall_call_set_header(d, "");
	yall_call_add_line(d, 0, "2");
	yall_call_add_line(d, 0, "1");
	yall_call_add_line(d, 0, "0");

	generate_call_msg(buffer, 0, d);

	cr_assert_str_eq(buffer, "");
}

/*
 * O.K.
 * Content too long
 */
Test(message, test_generate_call_message1)
{
	char buffer[2] = { 0 };
	yall_call_data *d = call_new();

	yall_call_set_header(d, "");
	yall_call_add_line(d, 0, "2");
	yall_call_add_line(d, 0, "1");
	yall_call_add_line(d, 0, "0");

	generate_call_msg(buffer, 2, d);

	cr_assert_str_eq(buffer, "\n");
}

/*
 * O.K.
 * Short lines
 */
Test(message, test_generate_call_message2)
{
	char buffer[64] = { 0 };
	yall_call_data *d = call_new();

	yall_call_set_header(d, "");
	yall_call_add_line(d, 0, "2");
	yall_call_add_line(d, 0, "1");
	yall_call_add_line(d, 0, "0");

	generate_call_msg(buffer, 32, d);

	cr_assert_str_eq(buffer, "\n2\n1\n0\n");
}

/*
 * O.K.
 * Longer lines
 */
Test(message, test_generate_call_message3)
{
	char buffer[64] = { 0 };
	yall_call_data *d = call_new();

	yall_call_set_header(d, "foo");
	yall_call_add_line(d, 0, "bar");
	yall_call_add_line(d, 0, "foobar");
	yall_call_add_line(d, 0, "foofoo");

	generate_call_msg(buffer, 32, d);

	cr_assert_str_eq(buffer, "foo\nbar\nfoobar\nfoofoo\n");
}

/*
 * Do not print '(null)' if header is not set
 */
Test(message, test_generate_call_message4)
{
	char buffer[64] = { 0 };
	yall_call_data *d = call_new();

	generate_call_msg(buffer, 64, d);

	cr_assert_str_eq(buffer, "\n");
}
