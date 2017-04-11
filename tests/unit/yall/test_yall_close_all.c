#include "test_yall.h"

extern uint16_t initialized;

/*
 * Library not init
 */
Test(yall, test_yall_close_all0)
{
	cr_assert_eq(yall_close_all(), YALL_NOT_INIT);
	cr_assert_eq(yall_close_all(), YALL_NOT_INIT);
}

Test(yall, test_yall_close_all1)
{
        initialized = 2;
        cr_assert_eq(yall_close_all(), YALL_OK);
        cr_assert_eq(initialized, 0);

        cr_assert_eq(yall_close_all(), YALL_NOT_INIT);
}
