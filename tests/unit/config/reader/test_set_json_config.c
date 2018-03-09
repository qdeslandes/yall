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

#include "config/reader/test.h"

/*
 * O.K.
 */
Test(config_reader, test_set_json_config0)
{
	set_json_config("std_header_template", json_string("std_header_template"));
	cr_assert_str_eq(current_config.std_header_template, "std_header_template");

	set_json_config("call_header_template", json_string("call_header_template"));
	cr_assert_str_eq(current_config.call_header_template, "call_header_template");

	set_json_config("tab_width", json_integer(3));
	cr_assert_eq(current_config.tab_width, 3);

	set_json_config("syslog_ident", json_string("syslog_ident"));
	cr_assert_str_eq(current_config.syslog_ident, "syslog_ident");

	set_json_config("syslog_facility", json_string("yall_fac_lpr"));
	cr_assert_eq(current_config.syslog_facility, yall_fac_lpr);
}

/*
 * Invalid key
 * Only check if it does not crash as we can't check if any of the configuration parameters have changed.
 */
Test(config_reader, test_set_json_config1)
{
	set_json_config("invalid_key", json_string("std_header_template"));
	set_json_config("invalid_key", json_integer(3));

	cr_assert(1);
}

/*
 * Invalid value for an existing key : integer as string or plain integer
 */
Test(config_reader, test_set_json_config2)
{
	set_json_config("tab_width", json_integer(7));
	cr_assert_eq(current_config.tab_width, 7);

	// As the used JSON type is invalid, nothing should change
	set_json_config("tab_width", json_string("3"));
	cr_assert_eq(current_config.tab_width, 7);
}

/*
 * Invalid value for an existing key : string as string or integer
 */
Test(config_reader, test_set_json_config3)
{
	set_json_config("call_header_template", json_string("3"));
	cr_assert_str_eq(current_config.call_header_template, "3");

	// As the used JSON type is invalid, nothing should change
	set_json_config("call_header_template", json_integer(7));
	cr_assert_str_eq(current_config.call_header_template, "3");
}
