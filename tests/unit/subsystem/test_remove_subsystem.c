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
 * Empty subsystems list
 */
Test(subsystem, test_remove_subsystem0)
{
	cr_assert_eq(remove_subsystem("0"), NULL);
	cr_assert_eq(remove_subsystem("nope"), NULL);
}

/*
 * O.K.
 * Non-empty subsystems list
 */
Test(subsystem, test_remove_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	struct yall_subsystem *s = NULL;

	// At the end
	cr_assert_eq((s = remove_subsystem("5")), _subsystems[15]);
	cr_assert_eq(_subsystems[10]->next, NULL);

	// In the middle without childs
	cr_assert_eq((s = remove_subsystem("1")), _subsystems[1]);
	cr_assert_eq(_subsystems[0]->next, _subsystems[2]);
	cr_assert_eq(_subsystems[2]->previous, _subsystems[0]);

	// With childs
	cr_assert_eq((s = remove_subsystem("2")), _subsystems[2]);
	cr_assert_eq(_subsystems[0]->next, _subsystems[3]);
	cr_assert_eq(s->childs, _subsystems[7]);
}

/*
 * O.K.
 * Remove the first one
 */
Test(subsystem, test_remove_subsystem2, .init=create_subsystems, .fini=clean_subsystems)
{
	struct yall_subsystem *s = NULL;

	cr_assert_eq((s = remove_subsystem("0")), _subsystems[0]);
	cr_assert_eq(subsystems, _subsystems[1]);
}

/*
 * O.K.
 * Remove the first child
 */
Test(subsystem, test_remove_subsystem3, .init=create_subsystems, .fini=clean_subsystems)
{
	struct yall_subsystem *s = NULL;

	cr_assert_eq((s = remove_subsystem("200")), _subsystems[8]);
	cr_assert_eq(_subsystems[7]->childs, _subsystems[9]);
	cr_assert_eq(_subsystems[9]->parent, _subsystems[7]);
}
