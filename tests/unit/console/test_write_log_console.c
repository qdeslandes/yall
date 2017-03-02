#include "test_console.h"

/*
 * Empty sentence to display
 */
ParameterizedTestParameters(console, test_write_log_console0) {
	return cr_make_param_array(struct param_set_color, ll_and_colors, 8);
}

ParameterizedTest(
	struct param_set_color *p,
	console,
	test_write_log_console0,
	.init=test_write_log_console_setup,
	.fini=test_write_log_console_clean)
{
	cr_assert_eq(write_log_console(p->ll, ""), YALL_OK);
	fflush(stderr);

	char output[10] = { 0 };
	sprintf(output, "\033[%dm\033[0m", p->code);
	cr_assert_stderr_eq_str(output);
}

/*
 * Non empty sentence to display
 */
ParameterizedTestParameters(console, test_write_log_console1) {
	return cr_make_param_array(struct param_set_color, ll_and_colors, 8);
}

ParameterizedTest(
	struct param_set_color *p,
	console,
	test_write_log_console1,
	.init=test_write_log_console_setup,
	.fini=test_write_log_console_clean)
{
	cr_assert_eq(write_log_console(p->ll, "sentence"), YALL_OK);
	fflush(stderr);

	char output[18] = { 0 };
	sprintf(output, "\033[%dmsentence\033[0m", p->code);
	cr_assert_stderr_eq_str(output);
}

/*
 * Failing sem_wait
 */
Test(console,
	test_write_log_console2,
	.init=test_write_log_console_setup,
	.fini=test_write_log_console_clean)
{
#ifdef __linux__
	disable_sem_init();
#elif _WIN32
#endif

	cr_assert_eq(write_log_console(yall_debug, "nope"), YALL_CONSOLE_LOCK_ERR);

#ifdef __linux__
	enable_sem_wait();
#elif _WIN32
#endif
}

/*
 * Failing fprintf
 */
Test(console,
	test_write_log_console3,
	.init=test_write_log_console_setup,
	.fini=test_write_log_console_clean)
{
	disable_fprintf();
	cr_assert_eq(write_log_console(yall_debug, "nope"), YALL_CONSOLE_WRITE_ERR);
	enable_fprintf();
}
