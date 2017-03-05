#include "test_subsystem.h"

static void tests_subsystem_setup(void)
{
	cr_redirect_stderr();
}

static void tests_subsystem_clean(void)
{

}

TestSuite(subsystem, .init=tests_subsystem_setup, .fini=tests_subsystem_clean);
