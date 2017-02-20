#include <criterion/criterion.h>
#include "yall/writer.h"
#include "yall/errors.h"
#include "h_stream.h"

#include <semaphore.h>
extern sem_t console_sem;
extern sem_t file_sem;

/*
 * It is not possible to test without initializing semaphores.
 * Currently, I can't test console / file output, so we only
 * checkout these functions return values.
 */
Test(subsystem, test_write_msg, .init=mutex_init, .fini=mutex_close)
{
	cr_assert_eq(write_msg(yall_console_output, yall_debug, NULL, ""), YALL_OK);

	cr_assert_eq(write_msg(yall_file_output, yall_debug, "out.log", ""), YALL_OK);
}
