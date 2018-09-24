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

#include "subsystem/test.h"

/*
 * O.K.
 * Empty subsystems list
 */
Test(subsystem, test_get_subsystem0)
{
	// Without parameters
	cr_assert_eq(get_subsystem("NONE", NULL), NULL);

	// With parameters
	struct yall_subsystem_params p = { 0 };
	cr_assert_eq(get_subsystem("NONE", &p), NULL);
	cr_assert_eq(p.log_level, yall_debug);
	cr_assert_eq(p.output_type, yall_console_output);
	cr_assert_eq(p.status, yall_subsys_enable);
	cr_assert_str_eq(p.file.filename, "yall.log");
}

/*
 * O.K.
 * Non-empty subsystems list
 */
Test(subsystem, test_get_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	// Without parameters
	cr_assert_eq(get_subsystem("0", NULL), _subsystems[0]);
	cr_assert_eq(get_subsystem("01", NULL), _subsystems[5]);
	cr_assert_eq(get_subsystem("201", NULL), _subsystems[9]);

	// With parameters
	struct yall_subsystem_params p = { 0 };

	cr_assert_eq(get_subsystem("1", &p), _subsystems[1]);
	cr_assert_eq(p.log_level, yall_notice);
	cr_assert_eq(p.status, yall_subsys_enable);
	cr_assert_eq(p.output_type, yall_console_output);

	cr_assert_eq(get_subsystem("02", &p), _subsystems[6]);
	cr_assert_eq(p.log_level, yall_warning);
	cr_assert_eq(p.status, yall_subsys_enable);
	cr_assert_eq(p.output_type, yall_console_output);

	cr_assert_eq(get_subsystem("200", &p), _subsystems[8]);
	cr_assert_eq(p.log_level, yall_warning);
	cr_assert_eq(p.status, yall_subsys_enable);
	cr_assert_eq(p.output_type, yall_console_output);
}
