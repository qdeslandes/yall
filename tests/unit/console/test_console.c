#include "test_console.h"

#include <criterion/criterion.h>
#include <criterion/redirect.h>

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

void tests_console_setup(void)
{
    cr_redirect_stderr();
}

void tests_console_clean(void)
{

}

/*
 * TODO : Write console tests for Windows.
 */

TestSuite(console, .init=tests_console_setup, .fini=tests_console_clean);
