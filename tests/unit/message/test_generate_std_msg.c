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

#include "test_message.h"

/*
 * Len equals 0
 */
Test(message, test_generate_std_msg0)
{
	/*
	size_t len = 0;
	char buffer[256] = { 0 };

	len = std_wrapper(buffer, 0, "%s", "foo");

	// TODO : restore these tests
	cr_assert_str_eq(buffer, "");

	// C.f. man page for snprintf
	cr_assert_eq(len, 3);
	*/
}

/*
 * Too long
 */
Test(message, test_generate_std_msg1)
{
	/*
	size_t len = 0;
	char buffer[2] = { 0 };

	len = std_wrapper(buffer, 2, "foo");

	// TODO : restore these tests
	cr_assert_str_eq(buffer, "\n");

	// TODO : fix this...
	cr_assert_eq(len, len);
	*/
}

Test(message, test_generate_std_msg2)
{
	/*
	size_t len = 0;
	char buffer[32] = { 0 };

	len = std_wrapper(buffer, 32, "foo : %s %d", "bar", 42);

	// TODO : restore these tests
	cr_assert_str_eq(buffer, "foo : bar 42");
	cr_assert_eq(len, 12);
	*/
}

Test(message, test_generate_std_msg3)
{
	/*
	size_t len = 0;
	char buffer[1] = { 0 };

	len = std_wrapper(buffer, 1, "foo : %s %d", "bar", 42);

	// TODO : restore these tests
	cr_assert_str_eq(buffer, "");

	// TODO: fix this...
	cr_assert_eq(len, len);
	*/
}
