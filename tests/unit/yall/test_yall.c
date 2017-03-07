#include "test_yall.h"

static void tests_yall_setup(void)
{
	_tests_hide_stderr();
}

static void tests_yall_clean(void)
{
	_tests_restore_stderr();
	remove(default_params.output_file);
}

TestSuite(yall, .init=tests_yall_setup, .fini=tests_yall_clean);


void tests_yall_init_lib(void)
{
	yall_init();
}

void tests_yall_close_lib(void)
{
	yall_close();
}

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

void tests_call_log_function(char *buffer, void *args)
{
	/*
	 * Writing function used in yall_call_log.
	 */
}
