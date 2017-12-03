#include "test_writer.h"

/*
 * Correct test
 */
Test(writer, test_writer_init0)
{
	cr_assert_eq(writer_init(60), YALL_SUCCESS);
}

/*
 * sem_init() fail
 */
Test(writer, test_writer_init1)
{
        disable_pthread_create();

	cr_assert_eq(writer_init(60), YALL_CANT_CREATE_THREAD);

        enable_pthread_create();
}
