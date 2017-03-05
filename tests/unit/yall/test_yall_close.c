#include "test_yall.h"

extern bool initialized;

/*
 * Not initialized
 */
Test(yall, test_yall_close0)
{
	cr_assert_eq(yall_close(), YALL_NOT_INIT);
}

/*
 * Initialized
 */
Test(yall, test_yall_close1)
{
	initialized = true;

	cr_assert_eq(yall_close(), YALL_OK);
	cr_assert_eq(yall_close(), YALL_NOT_INIT);
}
