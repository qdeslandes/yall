#include "test_writer.h"

/*
 * Correct test
 */
Test(writer, test_writer_init0)
{
	cr_assert_eq(writer_init(), YALL_OK);
}

/*
 * sem_init() fail
 */
Test(writer, test_writer_init1)
{
	disable_sem_init();
    printf("%X\n", writer_init());
	cr_assert_eq(writer_init(), YALL_SEM_INIT_ERR);
	enable_sem_init();
}
