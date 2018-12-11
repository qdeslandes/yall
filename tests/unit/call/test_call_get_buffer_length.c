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

#include "call/test.h"

/*
 * Empty call data
 */
Test(call, test_call_get_buffer_length0)
{
	struct yall_call_data *d = call_new();

	cr_assert_eq(call_get_buffer_length(d), 2);

	call_delete(d);
}

/*
 * Call data with header
 */
Test(call, test_call_get_buffer_length1)
{
	struct yall_call_data *d = call_new();

	yall_call_set_header(d, "testing");

	cr_assert_eq(call_get_buffer_length(d), 2 + strlen("testing"));

	call_delete(d);
}

/*
 * Call data with lines
 */
Test(call, test_call_get_buffer_length2)
{
	struct yall_call_data *d = call_new();

	yall_config_set_tab_width(2);

	yall_call_add_line(d, 1, "Hello ! %s", "world ?");

	cr_assert_eq(call_get_buffer_length(d), 22);

	call_delete(d);
}

/*
 * Call data with header and lines
 */
Test(call, test_call_get_buffer_length3)
{
	struct yall_call_data *d = call_new();

	yall_config_set_tab_width(2);

	yall_call_set_header(d, "testing");	// 7 characters
	yall_call_add_line(d, 1, "Hello !");	// 9 characters
	yall_call_add_line(d, 0, "%d", 32);	// 2 characters

	/*
	 * 18 characters
	 * + 3 ('\n' for each line)
	 * + 1 ('\0')
	 * + 4 (default 1 indent added to each line)
	 */

	cr_assert_eq(call_get_buffer_length(d), 26);

	call_delete(d);
}
