#include "test_yall.h"

extern bool initialized;

/*
 * Normal init
 */
Test(yall, test_yall_init0)
{
	cr_assert_eq(yall_init(), YALL_OK);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);

	yall_close();

	cr_assert_eq(yall_init(), YALL_OK);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
}

/*
 * Failed writer_init()
 */
Test(yall, test_yall_init1)
{
	disable_sem_init();
	cr_assert_eq(yall_init(), YALL_SEM_INIT_ERR);
	enable_sem_init();

	cr_assert_eq(yall_init(), YALL_OK);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);

	yall_close();

	cr_assert_eq(yall_init(), YALL_OK);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
}
