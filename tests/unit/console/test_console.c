#include "test_console.h"

struct param_set_color ll_and_colors[8] = {
	{ yall_debug, 97 },
	{ yall_info, 92 },
	{ yall_notice, 92 },
	{ yall_warning, 93 },
	{ yall_err, 91 },
	{ yall_crit, 91 },
	{ yall_alert, 91 },
	{ yall_emerg, 91 }
};

static void tests_console_setup(void)
{
	cr_redirect_stderr();
}

static void tests_console_clean(void)
{

}

TestSuite(console, .init=tests_console_setup, .fini=tests_console_clean);

#ifdef __linux__
#	include <semaphore.h>
extern sem_t console_sem;
#elif _WIN32
#	include <Windows.h>
extern HANDLE console_sem;
#endif

void test_write_log_console_setup(void)
{
#ifdef __linux__
	sem_init(&console_sem, 0, 1);
#elif _WIN32
	console_sem = CreateMutex(NULL, FALSE, NULL);
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
