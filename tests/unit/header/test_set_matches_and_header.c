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
 * Standard header
 */
Test(header, test_set_matches_and_header0)
{
	char *header = NULL;
	enum yall_matches *matches = NULL;

	set_matches_and_header(std_header, &header, &matches);

	cr_assert_eq(header, std_header_format);
	cr_assert_eq(matches, std_matches);
}

/*
 * O.K.
 * Call header
 */
Test(header, test_set_matches_and_header1)
{
	char *header = NULL;
	enum yall_matches *matches = NULL;

	set_matches_and_header(call_header, &header, &matches);

	cr_assert_eq(header, call_header_format);
	cr_assert_eq(matches, call_matches);
}

/*
 * Invalid header
 */
Test(header, test_set_matches_and_header2)
{
	char *header = NULL;
	enum yall_matches *matches = NULL;

	set_matches_and_header((enum yall_matches)4, &header, &matches);

	cr_assert_eq(header, std_header_format);
	cr_assert_eq(matches, std_matches);
}
