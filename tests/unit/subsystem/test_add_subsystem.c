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

#include "test_subsystem.h"

Test(subsystem, test_add_subsystem0)
{
        // Without parent
        struct yall_subsystem *s = get_fake_subsystem("0", NULL);
        add_subsystem(NULL, s);
        cr_assert_eq(subsystems, s);

        s = get_fake_subsystem("1", NULL);
        add_subsystem(NULL, s);
        cr_assert_eq(subsystems->next, s);
        cr_assert_eq(s->previous, subsystems);

        s = get_fake_subsystem("2", NULL);
        add_subsystem(NULL, s);
        cr_assert_eq(subsystems->next->next, s);
        cr_assert_eq(s->previous, subsystems->next);

        // With parent
        s = get_fake_subsystem("00", NULL);
        add_subsystem("0", s);
        cr_assert_eq(subsystems->childs, s);
        cr_assert_eq(s->parent, subsystems);

        s = get_fake_subsystem("20", NULL);
        add_subsystem("2", s);
        cr_assert_eq(subsystems->next->next->childs, s);
        cr_assert_eq(s->parent, subsystems->next->next);

        s = get_fake_subsystem("21", NULL);
        add_subsystem("2", s);
        cr_assert_eq(subsystems->next->next->childs->next, s);
        cr_assert_eq(s->parent, subsystems->next->next);
        cr_assert_eq(s->previous, subsystems->next->next->childs);

        // Without parent (last time)
        s = get_fake_subsystem("3", NULL);
        add_subsystem(NULL, s);
        cr_assert_eq(subsystems->next->next->next, s);
        cr_assert_eq(s->previous, subsystems->next->next);

        free_fake_subsystem(subsystems->next->next->next);
        free_fake_subsystem(subsystems->next->next->childs->next);
        free_fake_subsystem(subsystems->next->next->childs);
        free_fake_subsystem(subsystems->next->next);
        free_fake_subsystem(subsystems->next);
        free_fake_subsystem(subsystems->childs);
        free_fake_subsystem(subsystems);
        subsystems = NULL;
}
