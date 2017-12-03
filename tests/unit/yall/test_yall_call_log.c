#include "test_yall.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

/*
 * Library not initialized
 */
Test(yall, test_yall_call_log0)
{
        cr_assert_eq(yall_call_log("", yall_debug, "", "", 125, tests_call_log_function, NULL), YALL_NOT_INIT);
        cr_assert_eq(yall_call_log("nope", yall_debug, "", "", 0, tests_call_log_function, NULL), YALL_NOT_INIT);
        cr_assert_eq(yall_call_log("toolongnameforasubsysteminthelibrary", yall_debug, "", "main.c", 43, tests_call_log_function, NULL), YALL_NOT_INIT);
}

/*
 * Test on getting subsystem and checking log level
 */
TheoryDataPoints(yall, test_yall_call_log1) = {
        DataPoints(char *, "0", "00", "01", "02", "1", "2", "20", "200", "201", "3"),
        DataPoints(enum yall_log_level, yall_debug, yall_info, yall_notice, yall_warning, yall_err, yall_crit, yall_alert, yall_emerg),
	DataPoints(char *, "toolongnameforafunctionnameinthelibrary", "main", "int main()", "main()", "Class::Method", "int Class::Method", "int Class::Method()"),
	DataPoints(char *, "main.c", "C:/test/code/dev/main.c", "/mnt/storage/Projects/yall/yall.c", "MAIN.C", ""),
	DataPoints(int32_t, 123, 321, 0, 111111, 3, -1, 34)
};

Theory((char *s, enum yall_log_level ll, char *f, char *F, int32_t line), yall, test_yall_call_log1, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        uint8_t waiting_for = YALL_SUCCESS;
        uint8_t ret = yall_call_log(s, ll, f, F, line, tests_call_log_function, NULL);
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

        cr_assert_eq(yall_call_log("01", yall_emerg, "", "main.c", 43, tests_call_log_function, buff), YALL_SUCCESS);
        cr_assert_eq(yall_call_log("1", yall_emerg, "", "/mnt/main.c", 32, tests_call_log_function, buff), YALL_SUCCESS);
        cr_assert_eq(yall_call_log("200", yall_emerg, "", "C:/test/main.c", 32, tests_call_log_function, buff), YALL_SUCCESS);
}

/*
 * Disabled subsystem
 */
Test(yall, test_yall_call_log3, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        _subsystems[0]->status = yall_subsys_disable;

        cr_assert_eq(yall_call_log("0", yall_emerg, "", "main.c", 0, tests_call_log_function, NULL), YALL_SUBSYS_DISABLED);
}
