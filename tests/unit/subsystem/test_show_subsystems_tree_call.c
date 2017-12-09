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
	yall_enable_debug();
	yall_config_set_call_header_template("");
	yall_config_set_tab_width(0);

	struct yall_call_data d = { 0 };
	init_call_data(&d);

	show_subsystems_tree_call(&d, NULL);

	cr_assert_str_eq(d.header, "Subsystems tree :\n");

#ifdef __linux__
	cr_assert_str_eq(d.lines->content, "└── yall\n");
#else
	cr_assert_str_eq(d.lines->content, "|-- yall\n");
#endif
}

/*
 * Subsystems availables
 */
Test(subsystem, test_show_subsystems_tree_call1, .init=tests_yall_init_lib, .fini=tests_yall_close_lib)
{
	create_subsystems();

	yall_enable_debug();
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
