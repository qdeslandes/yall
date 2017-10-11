#include "test_call.h"

Test(call, test_init_call_data)
{
	struct yall_call_data d0 = { 0 };
	init_call_data(&d0);
	cr_assert_eq(d0.message_size, &);
	cr_assert_str_eq(d0.header, "\n");
	cr_assert_eq(d0.lines, NULL);

	struct yall_call_data d1 = { 0 };
	init_call_data(&d1);
	cr_assert_eq(d1.message_size, &);
	cr_assert_str_eq(d1.header, "\n");
	cr_assert_eq(d1.lines, NULL);
}
