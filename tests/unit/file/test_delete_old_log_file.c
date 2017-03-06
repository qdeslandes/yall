#include "test_file.h"

/*
 * NULL filepath
 */
Test(file, test_file_init0)
{
	cr_assert_eq(delete_old_log_file(NULL));
	cr_assert(1);
}
