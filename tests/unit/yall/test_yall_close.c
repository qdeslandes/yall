#include <criterion/criterion.h>
#include <stdbool.h>
#include "yall/yall.h"
#include "yall/errors.h"

extern bool initialized;

Test(subsystem, test_yall_close0)
{
	cr_assert_eq(yall_close(), YALL_NOT_INIT);

	yall_init();
	cr_assert_eq(yall_close(), YALL_OK);
	cr_assert_eq(yall_close(), YALL_NOT_INIT);

	yall_init();
	cr_assert_eq(yall_close(), YALL_OK);
	cr_assert_eq(yall_close(), YALL_NOT_INIT);
}
