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

#include "call/test.h"

/*
 * O.K.
 */
Test(call, test_yall_call_add_line0)
{	
	struct yall_call_data *d = call_data_new();

	yall_config_set_tab_width(2);
	yall_call_add_line(d, 0, "line");
	cr_assert_str_eq(ll_get_at(d->lines, 0), "  line\n");
	cr_assert_eq(d->message_size, strlen("  line\n") + 1);

	yall_config_set_tab_width(1);
	yall_call_add_line(d, 3, "new_line");
	cr_assert_str_eq(ll_get_at(d->lines, 1), "    new_line\n");
	cr_assert_eq(d->message_size, strlen("  line\n") + strlen("    new_line\n") + 1);

	yall_config_set_tab_width(0);
	yall_call_add_line(d, 1, "test %d %c", 3, 't');
	cr_assert_str_eq(ll_get_at(d->lines, 2), "test 3 t\n");
	cr_assert_eq(d->message_size, strlen("  line\n") + strlen("    new_line\n") + strlen("test 3 t\n") + 1);

	call_data_delete(d);
}
