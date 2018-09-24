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

#include "subsystem/test.h"

/*
 * O.K.
 * NULL parameters
 */
Test(subsystem, test_get_next_subsystem0, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	cr_assert_eq(get_next_subsystem(NULL, false, &d), NULL);
	cr_assert_eq(d, 0);
}

/*
 * O.K.
 * Subsystem with <childs>, crawling them
 */
Test(subsystem, test_get_next_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	// Crawling childs
	cr_assert_eq(get_next_subsystem(subsystems, true, &d), subsystems->childs);
	cr_assert_eq(d, 1);
}

/*
 * O.K.
 * Subsystem with <childs>, not crawling them, <next> available
 */
Test(subsystem, test_get_next_subsystem2, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	// Crawling childs
	cr_assert_eq(get_next_subsystem(_subsystems[2], false, &d), _subsystems[3]);
	cr_assert_eq(d, 0);
}

/*
 * O.K.
 * Subsystem without <next> neither <parent> or <childs>
 */
Test(subsystem, test_get_next_subsystem3, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	// Crawling childs
	cr_assert_eq(get_next_subsystem(_subsystems[15], false, &d), NULL);

	/*
	 * Here, there is no reason to test <d> as the function returned NULL.
	 */
}

/*
 * O.K.
 * Subsystem with a parent (who has a <next>), without <next> or <childs>
 */
Test(subsystem, test_get_next_subsystem4, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	// Crawling childs
	cr_assert_eq(get_next_subsystem(_subsystems[6], false, &d), _subsystems[1]);
	cr_assert_eq(d, -1);
}
