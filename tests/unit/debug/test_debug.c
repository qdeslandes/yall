#include "test_debug.h"

static void tests_debug_setup(void)
{
        cr_redirect_stderr();
}

static void tests_debug_clean(void)
{
        
}

TestSuite(debug, .init=tests_debug_setup, .fini=tests_debug_clean);