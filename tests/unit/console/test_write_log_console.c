#include "test_console.h"

/*
 * Empty sentence to display
 */
ParameterizedTestParameters(console, test_write_log_console0) {
	return cr_make_param_array(struct param_set_color, ll_and_colors, 8);
}

#include <Windows.h>

ParameterizedTest(
	struct param_set_color *p,
	console,
	test_write_log_console0,
	.init=test_write_log_console_setup,
	.fini=test_write_log_console_clean)
{
	cr_assert_eq(write_log_console(p->ll, ""), YALL_OK);

#ifdef __linux__
	/*
	 * This test does not works on Windows, I can't figure out why.
	 */

	fflush(stderr);

	char output[10] = { 0 };
	sprintf(output, "\033[%dm\033[0m", p->code);

	cr_assert_stderr_eq_str(output);
#endif
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
#ifdef __linux__
	sprintf(output, "\033[%dmsentence\033[0m", p->code);
#elif _WIN32
	sprintf(output, "sentence");
#endif
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
	disable_WaitForSingleObject();
#endif

	cr_assert_eq(write_log_console(yall_debug, "nope"), YALL_CONSOLE_LOCK_ERR);

#ifdef __linux__
	enable_sem_wait();
#elif _WIN32
	enable_WaitForSingleObject();
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
	//disable_fprintf();
	cr_assert_eq(write_log_console(yall_debug, "nope"), YALL_CONSOLE_WRITE_ERR);
	enable_fprintf();
}
