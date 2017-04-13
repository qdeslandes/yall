#include "test_yall.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

/*
 * Library not initialized
 */
Test(yall, test_yall_call_log0)
{
	cr_assert_eq(yall_call_log("", yall_debug, "", tests_call_log_function, NULL), YALL_NOT_INIT);
	cr_assert_eq(yall_call_log("nope", yall_debug, "", tests_call_log_function, NULL), YALL_NOT_INIT);
	cr_assert_eq(yall_call_log("toolongnameforasubsysteminthelibrary", yall_debug, "", tests_call_log_function, NULL), YALL_NOT_INIT);
}

/*
 * Test on getting subsystem and checking log level
 */
TheoryDataPoints(yall, test_yall_call_log1) = {
	DataPoints(char *, "0", "00", "01", "02", "1", "2", "20", "200", "201", "3"),
	DataPoints(enum yall_log_level, yall_debug, yall_info, yall_notice, yall_warning, yall_err, yall_crit, yall_alert, yall_emerg),
	DataPoints(char *, "toolongnameforafunctionnameinthelibrary", "main", "int main()", "main()", "Class::Method", "int Class::Method", "int Class::Method()"),
};

Theory((char *s, enum yall_log_level ll, char *f), yall, test_yall_call_log1, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
	uint8_t waiting_for = YALL_OK;
	uint8_t ret = yall_call_log(s, ll, f, tests_call_log_function, NULL);
	struct yall_subsystem_params p = { yall_warning, yall_file_output, yall_subsys_enable, "yall_default.log" };
	_get_subsystem(s, subsystems, &p);

	if (ll < p.log_level)
		waiting_for = YALL_LOG_LEVEL_TOO_LOW;

	cr_assert_eq(ret, waiting_for);
}

/*
 * Calling the logging function with parameters
 */
Test(yall, test_yall_call_log2, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
	char buff[40] = { 0 };

	cr_assert_eq(yall_call_log("01", yall_emerg, "", tests_call_log_function, buff), YALL_OK);
	cr_assert_eq(yall_call_log("1", yall_emerg, "", tests_call_log_function, buff), YALL_OK);
	cr_assert_eq(yall_call_log("200", yall_emerg, "", tests_call_log_function, buff), YALL_OK);
}

/*
 * Failed in writing message
 */
Test(yall, test_yall_call_log3, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
	disable_fprintf();
	cr_assert_eq(yall_call_log("01", yall_emerg, "", tests_call_log_function, NULL), YALL_CONSOLE_WRITE_ERR);
	enable_fprintf();
}

/*
 * Disabled subsystem
 */
Test(yall, test_yall_call_log4, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        _subsystems[0]->status = yall_subsys_disable;

        cr_assert_eq(yall_call_log("0", yall_emerg, "", tests_call_log_function, NULL), YALL_SUBSYS_DISABLED);
}
