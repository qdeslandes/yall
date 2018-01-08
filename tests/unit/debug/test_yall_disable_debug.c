#include "test_debug.h"

extern uint16_t initialized;
extern bool debug;
extern const char *debug_subsystem;

/*
 *Library not initialized
 */
Test(debug, test_yall_disable_debug0)
{
        cr_assert_eq(debug, false);
        
        cr_assert_eq(yall_disable_debug(), YALL_NOT_INIT);

        cr_assert_eq(debug, false);
}

/*
 * Multiple disabling
 */
Test(debug, test_yall_disable_debug1)
{
        cr_assert_eq(debug, false);

        yall_init();
        yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);
        yall_enable_debug("test");
        
        cr_assert_eq(debug, true);

        yall_disable_debug();
        cr_assert_eq(debug, false);
        cr_assert_eq(debug_subsystem, NULL);
        yall_disable_debug();
        cr_assert_eq(debug, false);
        cr_assert_eq(debug_subsystem, NULL);
}