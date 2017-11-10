#include "test_log_level.h"

Test(log_level, test_get_log_level_name0)
{
	cr_assert_str_eq(get_log_level_name(yall_debug), "DEBUG");
	cr_assert_str_eq(get_log_level_name(yall_info), "INFO");
	cr_assert_str_eq(get_log_level_name(yall_notice), "NOTICE");
	cr_assert_str_eq(get_log_level_name(yall_warning), "WARNING");
	cr_assert_str_eq(get_log_level_name(yall_err), "ERROR");
	cr_assert_str_eq(get_log_level_name(yall_crit), "CRITICAL");
	cr_assert_str_eq(get_log_level_name(yall_alert), "ALERT");
	cr_assert_str_eq(get_log_level_name(yall_emerg), "EMERGENCY");
}