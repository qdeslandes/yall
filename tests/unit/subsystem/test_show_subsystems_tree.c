#include "test_subsystem.h"
#include "helpers/h_subsystem.h"
#include "yall/test_yall.h"

extern void tests_yall_init_lib(void);
extern void tests_yall_close_lib(void);

/*
 * No debug mode
 */
Test(subsystem, test_show_subsystems_tree0, .init=tests_yall_init_lib, .fini=tests_yall_close_lib)
{
	yall_disable_debug();

	yall_show_subsystems_tree();
	cr_assert(1);

	/*
	 * TODO : it would be better, once show_subsystems_tree called to check
	 * stderr content.
	 */
}

/*
 * Debug mode
 */
Test(subsystem, test_show_subsystems_tree1, .init=tests_yall_init_lib, .fini=tests_yall_close_lib)
{
    yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);
	yall_enable_debug("test");

	yall_show_subsystems_tree();
	cr_assert(1);

	yall_disable_debug();

	/*
	 * TODO : it would be better, once show_subsystems_tree called to check
	 * stderr content.
	 */
}
