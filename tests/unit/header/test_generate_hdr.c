/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "header/test.h"

/*
 * O.K.
 * Do not write, only get required space
 */
Test(header, test_generate_hdr0, .init=test_init_yall, .fini=test_close_yall)
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
Test(header, test_generate_hdr1, .init=test_init_yall, .fini=test_close_yall)
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
