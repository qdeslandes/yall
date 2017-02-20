#include <criterion/criterion.h>
#include "yall/console.h"
#include "yall/errors.h"
#include "h_stream.h"

void reset_color(void);

Test(subsystem, test_reset_color0, .init=redirect_streams, .fini=restore_streams)
{
#if __linux
    reset_color();
    cr_assert_eq(check_stderr("\033[0m", 4), 0);

    reset_color();
    cr_assert_eq(check_stderr("\033[0m", 4), 0);
#elif _WIN32
	cr_assert(1);
#endif
}
