#include "test_yall.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

/*
 * Library not initialized
 */
Test(yall, test_yall_log0)
{
        cr_assert_eq(yall_log("", yall_debug, "", ""), YALL_NOT_INIT);
        cr_assert_eq(yall_log("nope", yall_debug, "", ""), YALL_NOT_INIT);
        cr_assert_eq(yall_log("toolongnameforasubsysteminthelibrary", yall_debug, "", ""), YALL_NOT_INIT);
}

/*
 * Empty subsystems list, so using the default subsystem
 */
Test(yall, test_yall_log1, .init=tests_yall_init_lib, .fini=tests_yall_close_lib)
{
        cr_assert_eq(yall_log("", yall_debug, "", ""), YALL_LOG_LEVEL_TOO_LOW);
        cr_assert_eq(yall_log("nope", yall_warning, "", ""), YALL_SUCCESS);
        cr_assert_eq(yall_log("toolongnameforasubsysteminthelibrary", yall_err, "", ""), YALL_SUCCESS);
}

/*
 * Test on getting subsystem and checking log level
 */
TheoryDataPoints(yall, test_yall_log2) = {
        DataPoints(char *, "0", "00", "01", "02", "1", "2", "20", "200", "201", "3"),
        DataPoints(enum yall_log_level, yall_debug, yall_info, yall_notice, yall_warning, yall_err, yall_crit, yall_alert, yall_emerg),
        DataPoints(char *, "toolongnameforafunctionnameinthelibrary", "main", "int main()", "main()", "Class::Method", "int Class::Method", "int Class::Method()"),
        DataPoints(char *, "")
};

Theory((char *s, enum yall_log_level ll, char *f, char *format), yall, test_yall_log2, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        uint8_t waiting_for = YALL_SUCCESS;
        uint8_t ret = yall_log(s, ll, f, format);
        struct yall_subsystem_params p = { yall_warning, yall_file_output, yall_subsys_enable, "yall_default.log" };
        _get_subsystem(s, subsystems, &p);

        if (ll < p.log_level)
                waiting_for = YALL_LOG_LEVEL_TOO_LOW;

        cr_assert_eq(ret, waiting_for);
}

/*
 * Variadic parameters list
 */
Test(yall, test_yall_log3, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        cr_assert_eq(yall_log("0", yall_emerg, "", "%s %d", "hello", 3), YALL_SUCCESS);
        cr_assert_eq(yall_log("3", yall_emerg, "", "%X %d", 4, 3), YALL_SUCCESS);
}

/*
 * Writing message error
 */
Test(yall, test_yall_log4, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        disable_fprintf();
        cr_assert_eq(yall_log("0", yall_emerg, "", ""), YALL_CONSOLE_WRITE_ERR);
        enable_fprintf();
}

/*
 * Disabled subsystem
 */
Test(yall, test_yall_log5, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        _subsystems[0]->status = yall_subsys_disable;

        cr_assert_eq(yall_log("0", yall_emerg, "", ""), YALL_SUBSYS_DISABLED);
}
