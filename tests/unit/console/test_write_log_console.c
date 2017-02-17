#include <criterion/criterion.h>
#include "yall/console.h"
#include "yall/errors.h"
#include "h_stream.h"

#include <semaphore.h>
extern sem_t console_sem;

Test(subsystem, test_write_log_console0, .init=redirect_streams, .fini=restore_streams)
{
    sem_init(&console_sem, 0, 1);

    cr_assert_eq(write_log_console(yall_debug, ""), YALL_OK);
    cr_assert_eq(check_stderr("\033[97m\033[0m", 9), 0);

    cr_assert_eq(write_log_console(yall_info, ""), YALL_OK);
    cr_assert_eq(check_stderr("\033[92m\033[0m", 9), 0);

    cr_assert_eq(write_log_console(yall_notice, ""), YALL_OK);
    cr_assert_eq(check_stderr("\033[92m\033[0m", 9), 0);

    cr_assert_eq(write_log_console(yall_warning, ""), YALL_OK);
    cr_assert_eq(check_stderr("\033[93m\033[0m", 9), 0);

    cr_assert_eq(write_log_console(yall_err, ""), YALL_OK);
    cr_assert_eq(check_stderr("\033[91m\033[0m", 9), 0);

    cr_assert_eq(write_log_console(yall_crit, ""), YALL_OK);
    cr_assert_eq(check_stderr("\033[91m\033[0m", 9), 0);

    cr_assert_eq(write_log_console(yall_alert, ""), YALL_OK);
    cr_assert_eq(check_stderr("\033[91m\033[0m", 9), 0);

    cr_assert_eq(write_log_console(yall_emerg, ""), YALL_OK);
    cr_assert_eq(check_stderr("\033[91m\033[0m", 9), 0);

    sem_destroy(&console_sem);
}

Test(subsystem, test_write_log_console1, .init=redirect_streams, .fini=restore_streams)
{
    sem_init(&console_sem, 0, 1);

    cr_assert_eq(write_log_console(yall_debug, "test"), YALL_OK);
    cr_assert_eq(check_stderr("\033[97mtest\033[0m", 13), 0);

    cr_assert_eq(write_log_console(yall_info, "test"), YALL_OK);
    cr_assert_eq(check_stderr("\033[92mtest\033[0m", 13), 0);

    cr_assert_eq(write_log_console(yall_notice, "test"), YALL_OK);
    cr_assert_eq(check_stderr("\033[92mtest\033[0m", 13), 0);

    cr_assert_eq(write_log_console(yall_warning, "test"), YALL_OK);
    cr_assert_eq(check_stderr("\033[93mtest\033[0m", 13), 0);

    cr_assert_eq(write_log_console(yall_err, "test"), YALL_OK);
    cr_assert_eq(check_stderr("\033[91mtest\033[0m", 13), 0);

    cr_assert_eq(write_log_console(yall_crit, "test"), YALL_OK);
    cr_assert_eq(check_stderr("\033[91mtest\033[0m", 13), 0);

    cr_assert_eq(write_log_console(yall_alert, "test"), YALL_OK);
    cr_assert_eq(check_stderr("\033[91mtest\033[0m", 13), 0);

    cr_assert_eq(write_log_console(yall_emerg, "test"), YALL_OK);
    cr_assert_eq(check_stderr("\033[91mtest\033[0m", 13), 0);

    sem_destroy(&console_sem);
}
