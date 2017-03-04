#include "test_console.h"

#ifdef __linux__

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

#endif