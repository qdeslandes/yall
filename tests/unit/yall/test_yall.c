#include "test_yall.h"

static void tests_yall_setup(void)
{
	cr_redirect_stderr();
}

static void tests_yall_clean(void)
{

}

TestSuite(yall, .init=tests_yall_setup, .fini=tests_yall_clean);


void tests_yall_log_setup(void)
{
	yall_init();
	create_subsystems();
}

void tests_yall_log_clean()
{
	clean_subsystems();
	yall_close();
}
