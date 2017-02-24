#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/redirect.h>

#include "h_utils.h"
#include "test_console.h"
#include "yall/console.h"
#include "yall/errors.h"

#ifdef __linux__
#include <semaphore.h>
extern sem_t console_sem;
#elif _WIN32
#include <Windows.h>
extern HANDLE console_sem;
#endif

void test_write_log_console_setup(void)
{
#ifdef __linux__
    sem_init(&console_sem, 0, 1);
#elif _WIN32
    console_sem = CreaMutex(NULL, FALSE, NULL);
#endif
}

void test_write_log_console_clean(void)
{
#ifdef __linux__
    sem_destroy(&console_sem);
#elif _WIN32
    CloseHandle(console_sem);
#endif
}

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
    DISABLE_SEM_WAIT();
    cr_assert_eq(write_log_console(yall_debug, "nope"), YALL_CONSOLE_LOCK_ERR);
    ENABLE_SEM_WAIT();
}

/*
 * Failing fprintf
 */
Test(console,
    test_write_log_console3,
    .init=test_write_log_console_setup,
    .fini=test_write_log_console_clean)
{
    DISABLE_FPRINTF();
    cr_assert_eq(write_log_console(yall_debug, "nope"), YALL_CONSOLE_WRITE_ERR);
    ENABLE_FPRINTF();
}
