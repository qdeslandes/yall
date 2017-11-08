#include "test_error.h"

static void tests_error_setup(void)
{
}

static void tests_error_clean(void)
{
}

TestSuite(error, .init=tests_error_setup, .fini=tests_error_clean);
