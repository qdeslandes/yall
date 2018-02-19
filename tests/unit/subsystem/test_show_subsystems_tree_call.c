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
#include "helpers/h_subsystem.h"
#include "yall/test_yall.h"

extern void tests_yall_init_lib(void);
extern void tests_yall_close_lib(void);
extern void show_subsystems_tree_call(struct yall_call_data *d, const void *args);

/*
 * Only 1 subsystem
 */
Test(subsystem, test_show_subsystems_tree_call0, .init=tests_yall_init_lib, .fini=tests_yall_close_lib)
{
    yall_set_subsystem("debug_subsys", NULL, yall_debug, yall_console_output, NULL);
	yall_enable_debug("debug_subsys");
	yall_config_set_call_header_template("");
	yall_config_set_tab_width(0);

	struct yall_call_data d = { 0 };
	init_call_data(&d);

	show_subsystems_tree_call(&d, NULL);

	cr_assert_str_eq(d.header, "Subsystems tree :\n");

#ifdef __linux__
	cr_assert_str_eq(d.lines->content, "└── debug_subsys\n");
#else
	cr_assert_str_eq(d.lines->content, "|-- debug_subsys\n");
#endif
}

/*
 * Subsystems availables
 */
Test(subsystem, test_show_subsystems_tree_call1, .init=tests_yall_init_lib, .fini=tests_yall_close_lib)
{
	create_subsystems();

    yall_set_subsystem("debug_subsys", NULL, yall_debug, yall_console_output, NULL);
	yall_enable_debug("debug_subsys");
	yall_config_set_call_header_template("");
	yall_config_set_tab_width(0);

	struct yall_call_data d = { 0 };
	init_call_data(&d);

	show_subsystems_tree_call(&d, NULL);

	cr_assert_str_eq(d.header, "Subsystems tree :\n");

#ifdef __linux__
	cr_assert_str_eq(d.lines->content, "├── 0\n");
	cr_assert_str_eq(d.lines->next->next->next->content, "│   └── 02\n");
#else
	cr_assert_str_eq(d.lines->content, "|-- 0\n");
	cr_assert_str_eq(d.lines->next->next->next->content, "|   |-- 02\n");
#endif
}

/*
 * No subsystems
 */
Test(subsystem, test_show_subsystems_tree_call2, .init=tests_yall_init_lib, .fini=tests_yall_close_lib)
{
	yall_config_set_call_header_template("");
	yall_config_set_tab_width(0);

	struct yall_call_data d = { 0 };
	init_call_data(&d);

	show_subsystems_tree_call(&d, NULL);

	cr_assert_str_eq(d.header, "Subsystems tree :\n");
	cr_assert_eq(d.lines, NULL);
}
