#include "test_debug.h"

extern uint16_t initialized;
extern bool debug;

/*
 * Activation
 */
Test(debug, test_yall_enable_debug0)
{
        yall_enable_debug();
        cr_assert_eq(debug, false);

        yall_init();
        yall_enable_debug();

        cr_assert_eq(debug, true);

        yall_close_all();

        cr_assert_eq(debug, false);

        yall_enable_debug();
        cr_assert_eq(debug, false);
}

/*
 * Subsystem creation
 */
Test(debug, test_yall_enable_debug1)
{
        yall_init();
        yall_enable_debug();

        cr_assert_eq(debug, true);
        struct yall_subsystem_params p = { 0 };
        cr_assert_str_eq(get_subsystem("yall", &p)->name, "yall");

        yall_close_all();
}
