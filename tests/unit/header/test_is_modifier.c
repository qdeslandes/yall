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
Test(header, test_is_modifier0)
{
	enum yall_matches match = match_empty;

	cr_assert_eq(is_modifier('s', &match), true);
	cr_assert_eq(match, match_subsystem);

	cr_assert_eq(is_modifier('l', &match), true);
	cr_assert_eq(match, match_log_level);

	cr_assert_eq(is_modifier('f', &match), true);
	cr_assert_eq(match, match_function);

	cr_assert_eq(is_modifier('F', &match), true);
	cr_assert_eq(match, match_filename);

	cr_assert_eq(is_modifier('L', &match), true);
	cr_assert_eq(match, match_line);

	cr_assert_eq(is_modifier('d', &match), true);
	cr_assert_eq(match, match_date);
}

/*
 * Is NOT a modifier
 */
Test(header, test_is_modifier1)
{
	enum yall_matches match = match_empty;

	cr_assert_eq(is_modifier('c', &match), false);
	cr_assert_eq(match, match_empty);

	cr_assert_eq(is_modifier('a', &match), false);
	cr_assert_eq(match, match_empty);
}
