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
 * O.K.
 */
Test(call, test_yall_call_set_header0)
{
	struct yall_call_data *d = call_data_new();

	yall_call_set_header(d, "header");
	cr_assert_str_eq(d->header, "header\n");
	cr_assert_eq(d->message_size, 7);

	yall_call_set_header(d, "header %c %d", 't', 3);
	cr_assert_str_eq(d->header, "header t 3\n");
	cr_assert_eq(d->message_size, 11);

	call_data_delete(d);
}

/*
 * Too long header
 */
Test(call, test_yall_call_set_header1)
{
	struct yall_call_data *d = call_data_new();

	yall_call_set_header(d, _TEST_1088_LONG_CALL_HEADER);
	cr_assert_str_eq(d->header, _TEST_1023_LONG_CALL_HEADER);
	cr_assert_eq(d->message_size, 1023);

	call_data_delete(d);
}
