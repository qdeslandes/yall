#include "test_debug.h"

extern uint16_t initialized;
extern bool debug;

Test(debug, test_yall_is_debug0)
{
        cr_assert_eq(yall_is_debug(), false);
        yall_init();
        cr_assert_eq(yall_is_debug(), false);
        yall_enable_debug();

        cr_assert_eq(debug, true);

        yall_disable_debug();
        cr_assert_eq(yall_is_debug(), false);
        yall_enable_debug();

        cr_assert_eq(debug, true);

        yall_close_all();
        cr_assert_eq(yall_is_debug(), false);
}
