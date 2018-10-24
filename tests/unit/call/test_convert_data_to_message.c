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
 * 0 sized buffer
 */
Test(call, test_convert_data_to_message0)
{
	struct yall_call_data d = { 0 };
	char buffer[16] = { 0 };

	convert_data_to_message(buffer, 0, &d);
	cr_assert_eq(buffer[0], '\0');
}

/*
 * O.K.
 * There is no need to call test_clean_2_call_data_lines as it is freed by the tested function
 */
Test(call, test_convert_data_to_message1, .init=test_2_call_data_lines)
{
	char buffer[16] = { 0 };

	convert_data_to_message(buffer, 16, &test_call_data);
	cr_assert_str_eq(buffer, "yalldatatest");
}
