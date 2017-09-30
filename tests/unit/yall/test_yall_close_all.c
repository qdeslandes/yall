#include "test_yall.h"

extern uint16_t initialized;

/*
 * Library not init
 */
Test(yall, test_yall_close_all0)
{
        yall_close_all();
        cr_assert_eq(initialized, 0);
}

Test(yall, test_yall_close_all1)
{
        initialized = 2;
        yall_close_all();
        cr_assert_eq(initialized, 0);

        yall_close_all();
        cr_assert_eq(initialized, 0);
}
