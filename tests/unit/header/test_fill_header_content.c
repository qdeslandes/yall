#include "test_header.h"

Test(header, test_fill_header_content0)
{
	struct header_content hc = { 0 };

	fill_header_content(&hc, "subsystem", yall_notice, "test_fill_header_content0");

	cr_assert_str_eq(hc.subsystem, "subsystem");
	cr_assert_str_eq(hc.log_level, "NOTICE");
	cr_assert_str_eq(hc.function_name, "test_fill_header_content0");
}