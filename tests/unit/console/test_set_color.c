#include <stdio.h>
#include <criterion/criterion.h>
#include "yall/console.h"
#include "yall/errors.h"
#include "h_stream.h"

void set_color(enum yall_log_level log_level);

Test(subsystem, test_set_color0, .init=redirect_streams, .fini=restore_streams)
{
#if __linux__
    set_color(yall_debug);
    cr_assert_eq(check_stderr("\033[97m", 5), 0);

    set_color(yall_info);
    cr_assert_eq(check_stderr("\033[92m", 5), 0);

    set_color(yall_notice);
    cr_assert_eq(check_stderr("\033[92m", 5), 0);

    set_color(yall_warning);
    cr_assert_eq(check_stderr("\033[93m", 5), 0);

    set_color(yall_err);
    cr_assert_eq(check_stderr("\033[91m", 5), 0);

    set_color(yall_crit);
    cr_assert_eq(check_stderr("\033[91m", 5), 0);

    set_color(yall_alert);
    cr_assert_eq(check_stderr("\033[91m", 5), 0);

    set_color(yall_emerg);
    cr_assert_eq(check_stderr("\033[91m", 5), 0);
#elif _WIN32
	cr_assert(1);
#endif
}
