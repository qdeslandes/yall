#include "test_message.h"

/*
 * Len equals 0
 */
Test(message, test_generate_std_msg0)
{
	/*
	size_t len = 0;
	char buffer[256] = { 0 };

	len = std_wrapper(buffer, 0, "%s", "foo");

	// TODO : restore these tests
	cr_assert_str_eq(buffer, "");

	// C.f. man page for snprintf
	cr_assert_eq(len, 3);
	*/
}

/*
 * Too long
 */
Test(message, test_generate_std_msg1)
{
	/*
	size_t len = 0;
	char buffer[2] = { 0 };

	len = std_wrapper(buffer, 2, "foo");

	// TODO : restore these tests
	cr_assert_str_eq(buffer, "\n");

	// TODO : fix this...
	cr_assert_eq(len, len);
	*/
}

Test(message, test_generate_std_msg2)
{
	/*
	size_t len = 0;
	char buffer[32] = { 0 };

	len = std_wrapper(buffer, 32, "foo : %s %d", "bar", 42);

	// TODO : restore these tests
	cr_assert_str_eq(buffer, "foo : bar 42");
	cr_assert_eq(len, 12);
	*/
}

Test(message, test_generate_std_msg3)
{
	/*
	size_t len = 0;
	char buffer[1] = { 0 };

	len = std_wrapper(buffer, 1, "foo : %s %d", "bar", 42);

	// TODO : restore these tests
	cr_assert_str_eq(buffer, "");

	// TODO: fix this...
	cr_assert_eq(len, len);
	*/
}
