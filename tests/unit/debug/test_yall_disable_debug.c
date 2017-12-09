#include "test_debug.h"

extern uint16_t initialized;
extern bool debug;

/*
 * Disactivation
 */
Test(debug, test_yall_disable_debug0)
{
        yall_disable_debug();
        cr_assert_eq(debug, false);

        yall_init();
        yall_enable_debug();
        yall_disable_debug();
        cr_assert_eq(debug, false);
        yall_close_all();
}

/*
 * Subsystem deletion
 */
Test(debug, test_yall_disable_debug1)
{
        yall_init();
        yall_enable_debug();

        cr_assert_eq(debug, true);

        yall_close_all();

        struct yall_subsystem_params p = { 0 };
        cr_assert_eq(get_subsystem("yall", &p), NULL);
}
