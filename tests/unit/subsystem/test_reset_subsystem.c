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
 */
Test(subsystem, test_reset_subsystem0)
{
	struct yall_subsystem *s = get_fake_subsystem("0", NULL);

	reset_subsystem(s);

	//cr_assert_str_eq(s->name, "");
	cr_assert_eq(s->log_level, yall_inherited_level);
	cr_assert_eq(s->status, yall_inherited_status);
	cr_assert_eq(s->output_type, yall_inherited_output);
	cr_assert_eq(s->delete_old_log_file, true);

	cr_assert_eq(s->file.filename, NULL);

	cr_assert_eq(s->parent, NULL);
	cr_assert_eq(s->childs, NULL);
	cr_assert_eq(s->previous, NULL);
	cr_assert_eq(s->next, NULL);

	free_fake_subsystem(s);
}
