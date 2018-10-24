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
 * No subsystems
 */
Test(subsystem, test_free_subsystems0)
{
	free_subsystems();

	cr_assert(1);
}

/*
 * O.K.
 * Fill subsystems
 */
Test(subsystem, test_free_subsystems1, .init=create_subsystems, .fini=clean_subsystems)
{
	free_subsystems();

	for (int i = 0; i < _NB_TEST_SUBSYSTEMS; ++i)
		_subsystems[i] = NULL;

	cr_assert(1);
}

/*
 * O.K.
 * Double free or corruption
 * Cause : when freeing subsystem, list pointer is not set to NULL, so reopening
 * the library will lead to adding a subsystem to the ghost one.
 */
Test(subsystem, test_free_subsystems2)
{
	yall_init();
	yall_set_subsystem("root", NULL, yall_debug, yall_console_output, NULL);
	yall_close_all();
	yall_init();
	yall_set_subsystem("root", NULL, yall_debug, yall_console_output, NULL);
	yall_close_all();
}
