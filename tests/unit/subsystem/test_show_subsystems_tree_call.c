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
 * Only 1 subsystem
 */
Test(subsystem, test_show_subsystems_tree_call0, .init=test_init_yall, .fini=test_close_yall)
{
	yall_set_subsystem("debug_subsys", NULL, yall_debug, yall_console_output, NULL);
	yall_enable_debug("debug_subsys");
	yall_config_set_call_header_template("");
	yall_config_set_tab_width(0);

	struct yall_call_data *d = call_data_new();

	show_subsystems_tree_call(d, NULL);

	cr_assert_str_eq(d->header, "Subsystems tree :\n");

#ifdef __linux__
	cr_assert_str_eq(ll_get_at(d->lines, 0), "└── debug_subsys\n");
#else
	cr_assert_str_eq(ll_get_at(d->lines, 0), "|-- debug_subsys\n");
#endif
}

/*
 * O.K.
 * Many subsystems availables
 */
Test(subsystem, test_show_subsystems_tree_call1, .init=test_init_yall, .fini=test_close_yall)
{
	create_subsystems();

	yall_set_subsystem("debug_subsys", NULL, yall_debug, yall_console_output, NULL);
	yall_enable_debug("debug_subsys");
	yall_config_set_call_header_template("");
	yall_config_set_tab_width(0);

	struct yall_call_data *d = call_data_new();

	show_subsystems_tree_call(d, NULL);

	cr_assert_str_eq(d->header, "Subsystems tree :\n");

#ifdef __linux__
	cr_assert_str_eq(ll_get_at(d->lines, 0), "├── 0\n");
	cr_assert_str_eq(ll_get_at(d->lines, 3), "│   └── 02\n");
#else
	cr_assert_str_eq(ll_get_at(d->lines, 0), "|-- 0\n");
	cr_assert_str_eq(ll_get_at(d->lines, 3), "|   |-- 02\n");
#endif
}

/*
 * O.K.
 * No subsystems
 */
Test(subsystem, test_show_subsystems_tree_call2, .init=test_init_yall, .fini=test_close_yall)
{
	yall_config_set_call_header_template("");
	yall_config_set_tab_width(0);

	struct yall_call_data *d = call_data_new();

	show_subsystems_tree_call(d, NULL);

	cr_assert_str_eq(d->header, "Subsystems tree :\n");
}
