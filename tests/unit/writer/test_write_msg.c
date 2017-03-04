#include "test_writer.h"

/*
 * This function only call a writer. No test is done on the data, so it can't
 * fail.
 */
Test(subsystem, test_write_msg, .init=_tests_mutex_init, .fini=_tests_mutex_close)
{
	cr_assert_eq(write_msg(yall_console_output, yall_debug, NULL, ""), YALL_OK);

	cr_assert_eq(write_msg(yall_file_output, yall_debug, NULL_FILE, ""), YALL_OK);
}
