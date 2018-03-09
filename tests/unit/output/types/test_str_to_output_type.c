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

#include "output/types/test.h"

ParameterizedTestParameters(output_types, test_str_to_output_type0) {
	static struct output_type_set params[] = {
		{ "yall_console_output", yall_console_output },
		{ "yall_file_output", yall_file_output },
		{ "yall_syslog_output", yall_syslog_output },
		{ "yall_inherited_output", yall_inherited_output }
	};

	return cr_make_param_array(struct output_type_set, params, 4);
}

/*
 * O.K.
 * Existing output type
 */
ParameterizedTest(struct output_type_set *p, output_types, test_str_to_output_type0)
{
	cr_assert_eq(p->output_type, str_to_output_type(p->output_type_str));
}

/*
 * O.K.
 * NULL parameter
 */
Test(output_types, test_str_to_output_type1)
{
	cr_assert_eq(yall_console_output, str_to_output_type(NULL));
}

/*
 * O.K.
 * Non existing output type
 */
Test(output_types, test_str_to_output_type2)
{
	cr_assert_eq(yall_console_output, str_to_output_type("invalid"));
}
