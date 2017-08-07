#include "test_writer.h"

/*
 * Correct test
 */
Test(writer, test_writer_init0)
{
	cr_assert_eq(writer_init(60), YALL_OK);
}

/*
 * sem_init() fail
 */
Test(writer, test_writer_init1)
{
#ifdef __linux__
        disable_sem_init();
#elif _WIN32
        disable_CreateMutex();
#endif

	cr_assert_eq(writer_init(60), YALL_SEM_INIT_ERR);

#ifdef __linux__
        enable_sem_init();
#elif _WIN32
        enable_CreateMutex();
#endif
}
