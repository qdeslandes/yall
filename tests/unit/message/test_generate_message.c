#include "test_message.h"

/*
 * generate_header() failure
 */
Test(message, test_generate_message0)
{
	char buffer[YALL_MSG_LEN] = { 0 };

	//disable_snprintf();
	cr_assert_eq(wrapper(buffer, "", "test", yall_debug, "test"), YALL_STRING_WRITE_ERR);
	enable_snprintf();
}

/*
 * vsnprintf() failure
 */
Test(message, test_generate_message1)
{
	char buffer[YALL_MSG_LEN] = { 0 };

	//disable_vsnprintf();
	cr_assert_eq(wrapper(buffer, "", "test", yall_debug, "test"), YALL_STRING_WRITE_ERR);
	enable_vsnprintf();
}

/*
 * Message too long
 */
Test(message, test_generate_message2)
{
	char buffer[YALL_MSG_LEN] = { 0 };
	char too_long_string[512] =  "\
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000 \
		000000000000000000000000000000000000000000000000  ";

	cr_assert_eq(wrapper(buffer, too_long_string, "test", yall_debug, "test"), YALL_OK);
}
