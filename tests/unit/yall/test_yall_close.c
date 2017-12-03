#include "test_yall.h"

extern uint16_t initialized;

/*
 * Not initialized
 */
Test(yall, test_yall_close0)
{
        cr_assert_eq(yall_close(), YALL_NOT_INIT);
}

/*
 * Initialized
 */
Test(yall, test_yall_close1)
{
	yall_init();
	yall_init();

        cr_assert_eq(yall_close(), YALL_SUCCESS);
        cr_assert_eq(initialized, 1);
        cr_assert_eq(yall_close(), YALL_SUCCESS);
        cr_assert_eq(initialized, 0);
        cr_assert_eq(yall_close(), YALL_NOT_INIT);
}
