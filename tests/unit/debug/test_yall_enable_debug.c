#include "test_debug.h"

extern uint16_t initialized;
extern bool debug;
extern const char *debug_subsystem;

/*
 * Library not initialized
 */
Test(debug, test_yall_enable_debug0)
{
        cr_assert_eq(debug, false);

        cr_assert_eq(yall_enable_debug(""), YALL_NOT_INIT);

        cr_assert_eq(debug, false);
}

/*
 * subsystem does not exists
 */
Test(debug, test_yall_enable_debug1)
{
        cr_assert_eq(debug, false);

        yall_init();

        cr_assert_eq(yall_enable_debug("test"), YALL_SUBSYS_NOT_EXISTS);

        cr_assert_eq(debug, false);
}

/*
 * Working test
 */
Test(debug, test_yall_enable_debug2)
{
        cr_assert_eq(debug, false);

        yall_init();
        yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);

        cr_assert_eq(YALL_SUCCESS, yall_enable_debug("test"));
        cr_assert_str_eq(debug_subsystem, "test");
        cr_assert_eq(debug, true);
}