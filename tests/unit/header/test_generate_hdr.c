#include "test_header.h"

extern size_t generate_hdr(enum header_type hdr_type, char *buffer, size_t len, struct header_content *hc);

/*
 * Do not write
 */
Test(header, test_generate_hdr0, .init=test_generate_hdr_setup, .fini=test_generate_hdr_clean)
{
	size_t len = 0;
	yall_config_set_std_header_template("%s");
	yall_config_set_call_header_template("%f");
	struct header_content hc = { "subsystem", "NOTICE", "function", "main.c", { 0 }, { 0 }  };

	len = generate_hdr(std_header, NULL, 0, &hc);
	cr_assert_eq(len, strlen(hc.subsystem));
	len = generate_hdr(call_header, NULL, 0, &hc);
	cr_assert_eq(len, strlen(hc.function_name));

	yall_config_set_std_header_template("%s : %f");
	yall_config_set_call_header_template("%l : %f");

	len = generate_hdr(std_header, NULL, 0, &hc);
	cr_assert_eq(len, strlen(hc.subsystem) + strlen(hc.function_name) + 3);
	len = generate_hdr(call_header, NULL, 0, &hc);
	cr_assert_eq(len, strlen(hc.log_level) + strlen(hc.function_name) + 3);
}

/*
 * Write the header
 */
Test(header, test_generate_hdr1, .init=test_generate_hdr_setup, .fini=test_generate_hdr_clean)
{
	size_t len = 0;
	char header[64] = { 0 };
	yall_config_set_std_header_template("%s");
	yall_config_set_call_header_template("%f");
	struct header_content hc = { "subsystem", "NOTICE", "function", "main.c", { 0 }, { 0 }  };

	len = generate_hdr(std_header, header, 64, &hc);
	cr_assert_eq(len, strlen(hc.subsystem));
	cr_assert_str_eq(header, hc.subsystem);
	len = generate_hdr(call_header, header, 64, &hc);
	cr_assert_eq(len, strlen(hc.function_name));
	cr_assert_str_eq(header, hc.function_name);

	yall_config_set_std_header_template("%s : %f");
	yall_config_set_call_header_template("%l : %f");

	len = generate_hdr(std_header, header, 64, &hc);
	cr_assert_eq(len, strlen(hc.subsystem) + strlen(hc.function_name) + 3);
	cr_assert_str_eq(header, "subsystem : function");
	len = generate_hdr(call_header, header, 64, &hc);
	cr_assert_eq(len, strlen(hc.log_level) + strlen(hc.function_name) + 3);
	cr_assert_str_eq(header, "NOTICE : function");
}