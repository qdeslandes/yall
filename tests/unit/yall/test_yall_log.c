#include <criterion/criterion.h>
#include <criterion/theories.h>

#include "h_subsystem.h"
#include "yall/yall.h"
#include "yall/errors.h"
#include "yall/subsystem.h"

extern struct yall_subsystem *subsystems;

void tests_yall_log_init()
{
	yall_init();
	cr_redirect_stderr();
	create_subsystems();
}

void tests_yall_log_clean()
{
	clean_subsystems();
	yall_close();
}

/*
 * Empty subsystems list
 */
Test(yall, test_yall_log0)
{
	cr_assert_eq(yall_log("", yall_debug, "", ""), YALL_SUBSYS_NOT_EXISTS);
	cr_assert_eq(yall_log("nope", yall_debug, "", ""), YALL_SUBSYS_NOT_EXISTS);
	cr_assert_eq(yall_log("toolongnameforasubsysteminthelibrary", yall_debug, "", ""), YALL_SUBSYS_NOT_EXISTS);
}

/*
 * Test on getting subsystem and checking log level
 */
TheoryDataPoints(yall, test_yall_log1) = {
	DataPoints(const char *, "0", "00", "01", "02", "1", "2", "20", "200", "201", "3"),
	DataPoints(enum yall_log_level, yall_debug, yall_info, yall_notice, yall_warning, yall_err, yall_crit, yall_alert, yall_emerg),
	DataPoints(const char *, "toolongnameforafunctionnameinthelibrary", "main", "int main()", "main()", "Class::Method", "int Class::Method", "int Class::Method()"),
	DataPoints(const char *, "")
};

Theory((const char *s, enum yall_log_level ll, const char *f, const char *format), yall, test_yall_log1, .init=tests_yall_log_init, .fini=tests_yall_log_clean)
{
	uint8_t waiting_for = YALL_OK;
	uint8_t ret = yall_log(s, ll, f, format);
	struct yall_subsystem_params p = { yall_warning, yall_file_output, "app.log" };
	struct yall_subsystem *subsys = _get_subsystem(s, subsystems, &p);

	if (ll < p.log_level)
		waiting_for = YALL_LOG_LEVEL_TOO_LOW;

	cr_assert_eq(ret, waiting_for);
}

/*
 * Failing message string allocation
 */
Test(yall, test_yall_log2, .init=tests_yall_log_init, .fini=tests_yall_log_clean)
{
	disable_malloc();
	cr_assert_eq(yall_log("3", yall_emerg, "", ""), YALL_NO_MEM);
	enable_malloc();
}

/*
 * Variadic parameters list
 */
Test(yall, test_yall_log3, .init=tests_yall_log_init, .fini=tests_yall_log_clean)
{
	cr_assert_eq(yall_log("0", yall_emerg, "", "%s %d", "hello", 3), YALL_OK);
	cr_assert_eq(yall_log("3", yall_emerg, "", "%X %d", 4, 3), YALL_OK);
}

/*
 * Writing message error
 */
Test(yall, test_yall_log4, .init=tests_yall_log_init, .fini=tests_yall_log_clean)
{
	disable_fprintf();
	cr_assert_eq(yall_log("0", yall_emerg, "", "%s %d", "hello", 3), YALL_CONSOLE_WRITE_ERR);
	cr_assert_eq(yall_log("3", yall_emerg, "", "%X %d", 4, 3), YALL_CONSOLE_WRITE_ERR);
	enable_fprintf();
}