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
 * No subsystem available
 */
Test(subsystem, test_set_subsys_status0)
{
	set_subsys_status("test", yall_subsys_disable);
	set_subsys_status("test", yall_subsys_enable);

	cr_assert(1);
}

/*
 * O.K.
 * With test subsystems
 */
Test(subsystem, test_set_subsys_status1, .init=create_subsystems, .fini=clean_subsystems)
{
	set_subsys_status("0", yall_subsys_disable);
	cr_assert_eq(_subsystems[0]->status, yall_subsys_disable);

	set_subsys_status("01", yall_subsys_disable);
	cr_assert_eq(_subsystems[5]->status, yall_subsys_disable);
}
