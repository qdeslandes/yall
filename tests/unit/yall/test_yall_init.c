#include "test_yall.h"

extern bool initialized;

/*
 * Normal init
 */
Test(yall, test_yall_init0)
{
	cr_assert_eq(yall_init(), YALL_OK);
        cr_assert_eq(initialized, true);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
        cr_assert_eq(initialized, true);

	yall_close();

	cr_assert_eq(yall_init(), YALL_OK);
        cr_assert_eq(initialized, true);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
        cr_assert_eq(initialized, true);
}

/*
 * Failed writer_init()
 */
Test(yall, test_yall_init1)
{
#ifdef __linux__
	disable_sem_init();
#elif _WIN32
	disable_CreateMutex();
#endif

	cr_assert_eq(yall_init(), YALL_SEM_INIT_ERR);

#ifdef __linux__
	enable_sem_init();
#elif _WIN32
	enable_CreateMutex();
#endif

	cr_assert_eq(yall_init(), YALL_OK);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);

	yall_close();

	cr_assert_eq(yall_init(), YALL_OK);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
}
