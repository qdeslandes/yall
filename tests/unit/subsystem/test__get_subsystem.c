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
 * TODO : Check the returned file name in case of file output type.
 */

/*
 * O.K.
 * Empty subsystems list
 */
Test(subsystem, test__get_subsystem0)
{
	// Without parameters
	cr_assert_eq(_get_subsystem("", subsystems, NULL), NULL);
	cr_assert_eq(_get_subsystem("test", subsystems, NULL), NULL);

	// With parameters
	struct yall_subsystem_params p = { 0 };
	cr_assert_eq(_get_subsystem("", subsystems, &p), NULL);
	cr_assert_eq(_get_subsystem("test", subsystems, &p), NULL);
}

/*
 * O.K.
 * Filled subsystems list
 */
Test(subsystem, test__get_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	// Without parameters
	cr_assert_eq(_get_subsystem("", subsystems, NULL), NULL);
	cr_assert_eq(_get_subsystem("204", subsystems, NULL), NULL);
	cr_assert_eq(_get_subsystem("0", subsystems, NULL), _subsystems[0]);
	cr_assert_eq(_get_subsystem("01", subsystems, NULL), _subsystems[5]);
	cr_assert_eq(_get_subsystem("200", subsystems, NULL), _subsystems[8]);

	// With parameters, using subsystems 0, 01 and 201
	struct yall_subsystem_params p = { 0 };
	cr_assert_eq(_get_subsystem("0", subsystems, &p), _subsystems[0]);
	cr_assert_eq(p.log_level, yall_debug);
	cr_assert_eq(p.output_type, yall_console_output);

	cr_assert_eq(_get_subsystem("01", subsystems, &p), _subsystems[5]);
	cr_assert_eq(p.log_level, yall_debug);
	cr_assert_eq(p.output_type, yall_console_output);

	cr_assert_eq(_get_subsystem("201", subsystems, &p), _subsystems[9]);
	cr_assert_eq(p.log_level, yall_debug);
	cr_assert_eq(p.output_type, yall_console_output);
}

/*
 * O.K.
 * Test if the parameters are shallowed :
 * 	- subsystem 4
 * 	  |- subsystem 40
 * 	  |  |- subsystem 400
 * 	  |- subsystem 41
 * 		 |- subsystem 410
 * This way, if subsystem 41 inherit from subsystem 4 but subsystem 40 does not,
 * the parameters should not be shallowed.
 */
Test(subsystem, test__get_subsystem2, .init=create_subsystems, .fini=clean_subsystems)
{
	struct yall_subsystem_params p = { 0 };
	cr_assert_eq(_get_subsystem("41", subsystems, &p), _subsystems[13]);

	/*
	 * Here, p.log_level should have the value of subsystem 4
	 * (_subsystems[10]), but it has the value of subsystem 40
	 * (_subsystems[11]).
	 */
	cr_assert_eq(p.log_level, _subsystems[10]->log_level);
}
