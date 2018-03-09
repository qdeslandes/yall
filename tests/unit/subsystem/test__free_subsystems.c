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
 * NULL parameter
 */
Test(subsystem, test__free_subsystems0)
{
	_free_subsystems(NULL);

	cr_assert(1);
}

/*
 * O.K.
 * Free complete trees
 */
Test(subsystem, test__free_subsystems1, .init=create_subsystems)
{
	_free_subsystems(subsystems->childs);
	cr_assert_eq(subsystems->childs, NULL);

	_free_subsystems(subsystems->next->next->childs->childs);
	cr_assert_eq(subsystems->next->next->childs->childs, NULL);

	_free_subsystems(subsystems);

	for (int i = 0; i < _NB_TEST_SUBSYSTEMS; ++i)
		_subsystems[i] = NULL;

	cr_assert(1);
}
