#include "test_yall.h"

extern uint16_t initialized;

/*
 * Library not init
 */
Test(yall, test_yall_is_initl0)
{
        cr_assert_eq(yall_is_init(), initialized);

        initialized = 2;
        cr_assert_eq(yall_is_init(), initialized);

        yall_init();
        yall_close_all();
        cr_assert_eq(yall_is_init(), initialized);
        cr_assert_eq(yall_is_init(), 0);
}
