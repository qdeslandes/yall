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

#include "test_error.h"

extern struct yall_errordesc {
	yall_error code;
	const char *message;
} errordesc[];

/*
 * Value too low
 */
Test(error, test_yall_strerror0)
{
	cr_assert_str_eq(yall_strerror((yall_error)-1), errordesc[YALL_UNKNOW_ERROR].message);
}

/*
 * Value too high
 */
Test(error, test_yall_strerror1)
{
	cr_assert_str_eq(yall_strerror(yall_err_end), errordesc[YALL_UNKNOW_ERROR].message);

	cr_assert_str_eq(yall_strerror(yall_err_end+1), errordesc[YALL_UNKNOW_ERROR].message);
}

/*
 * Correct value
 */
Test(error, test_yall_strerror2)
{
	for (int i = 0; i < yall_err_end; ++i) {
		const char *str = errordesc[i].message;
		cr_assert_str_eq(yall_strerror(i), str);
	}
}