#include "test_yall.h"

extern struct yall_subsystem *subsystems;

/*
 * Bad name
 */
Test(yall, test_yall_set_subsystem0, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
	cr_assert_eq(yall_set_subsystem(NULL, NULL, yall_debug, yall_console_output, NULL), YALL_NO_NAME);
}

/*
 * Need to update an existing subsystem
 */
Test(yall, test_yall_set_subsystem1, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
	cr_assert_eq(yall_set_subsystem("0", NULL, yall_debug, yall_console_output, NULL), YALL_OK);
}

/*
 * Need to create a subsystem
 */
Test(yall, test_yall_set_subsystem2, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
	cr_assert_eq(yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL), YALL_OK);
}

/*
 * create_subsystem() fail
 */
Test(yall, test_yall_set_subsystem3, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
	disable_malloc();
	cr_assert_eq(yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL), YALL_CANT_CREATE_SUBSYS);
	enable_malloc();
}
