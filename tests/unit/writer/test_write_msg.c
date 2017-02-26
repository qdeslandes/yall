#include <criterion/criterion.h>
#include "yall/writer.h"
#include "yall/errors.h"
#include "h_stream.h"

/*
 * This function only call a writer. No test is done on the data, so it can't
 * fail.
 */
Test(subsystem, test_write_msg, .init=mutex_init, .fini=mutex_close)
{
	cr_assert_eq(write_msg(yall_console_output, yall_debug, NULL, ""), YALL_OK);

	cr_assert_eq(write_msg(yall_file_output, yall_debug, "/dev/null", ""), YALL_OK);
}
