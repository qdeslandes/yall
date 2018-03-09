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
 * No parent, no existing subsystem
 */
Test(subsystem, test_add_subsystem0)
{
	struct yall_subsystem *s = get_fake_subsystem("0", NULL);
	add_subsystem(NULL, s);

	cr_assert_eq(subsystems, s);

	_free_subsystems(subsystems);
	subsystems = NULL;
}

/*
 * O.K.
 * No parent, existing subsystems
 */
Test(subsystem, test_add_subsystem1)
{
	struct yall_subsystem *s = get_fake_subsystem("0", NULL);
	add_subsystem(NULL, s);

	s = get_fake_subsystem("1", NULL);
	add_subsystem(NULL, s);

	cr_assert_eq(subsystems->next, s);
	cr_assert_eq(s->previous, subsystems);

	_free_subsystems(subsystems);
	subsystems = NULL;
}

/*
 * O.K.
 * Parent (non-existing), no existing subsystems
 */
Test(subsystem, test_add_subsystem2)
{
	struct yall_subsystem *s = get_fake_subsystem("0", NULL);
	add_subsystem("invalid", s);

	cr_assert_eq(subsystems, s);
	cr_assert_eq(s->parent, NULL);

	_free_subsystems(subsystems);
	subsystems = NULL;
}

/*
 * O.K.
 * Parent (non-existing), existing subsystems
 */
Test(subsystem, test_add_subsystem3)
{
	struct yall_subsystem *s = get_fake_subsystem("0", NULL);
	add_subsystem(NULL, s);

	s = get_fake_subsystem("1", NULL);
	add_subsystem("invalid", s);

	cr_assert_eq(subsystems->next, s);
	cr_assert_eq(s->previous, subsystems);
	cr_assert_eq(s->parent, NULL);

	_free_subsystems(subsystems);
	subsystems = NULL;
}

/*
 * O.K.
 * Parent, existing subsystems
 */
Test(subsystem, test_add_subsystem4)
{
	struct yall_subsystem *s = get_fake_subsystem("0", NULL);
	add_subsystem(NULL, s);

	s = get_fake_subsystem("1", NULL);
	add_subsystem("0", s);

	cr_assert_eq(subsystems->childs, s);
	cr_assert_eq(s->previous, NULL);
	cr_assert_eq(s->parent, subsystems);

	_free_subsystems(subsystems);
	subsystems = NULL;
}

/*
 * O.K.
 * Add a brother to a child
 */
Test(subsystem, test_add_subsystem5)
{
	struct yall_subsystem *s = get_fake_subsystem("0", NULL);
	add_subsystem(NULL, s);
	s = get_fake_subsystem("1", NULL);
	add_subsystem("0", s);
	s = get_fake_subsystem("2", NULL);
	add_subsystem("0", s);

	cr_assert_eq(subsystems->childs->next, s);
	cr_assert_eq(s->previous, subsystems->childs);
	cr_assert_eq(s->parent, subsystems);

	_free_subsystems(subsystems);
	subsystems = NULL;
}
