#include "test_yall.h"

extern uint16_t initialized;

/*
 * Normal init
 */
Test(yall, test_yall_init0)
{
        cr_assert_eq(yall_init(), YALL_SUCCESS);
        cr_assert_eq(initialized, 1);
        cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
        cr_assert_eq(initialized, 2);

        yall_close();

        cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
        cr_assert_eq(initialized, 2);
        cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
        cr_assert_eq(initialized, 3);
}

/*
 * Failed writer_init()
 */
Test(yall, test_yall_init1)
{
        disable_pthread_create();

        cr_assert_eq(yall_init(), YALL_CANT_CREATE_THREAD);
        cr_assert_eq(initialized, 0);

        enable_pthread_create();

        cr_assert_eq(yall_init(), YALL_SUCCESS);
        cr_assert_eq(initialized, 1);
        cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
        cr_assert_eq(initialized, 2);

        yall_close();

        cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
        cr_assert_eq(initialized, 2);
}
