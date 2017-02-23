#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "yall/console.h"

void reset_color(void);

Test(console, test_reset_color0)
{
    reset_color();
    fflush(stderr);
    cr_assert_stderr_eq_str("\033[0m");

    /*
     * TODO : Try to call reset_color() a second time.
     * Currently crash if it is done.
     */
}
