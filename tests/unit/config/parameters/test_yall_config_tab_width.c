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

#include "config/parameters/test.h"

/*
 * O.K.
 * Getter.
 */
Test(config_parameters, test_yall_config_set_tab_width0, .init=test_yall_init, .fini=test_yall_close)
{
	yall_config_set_tab_width(0);
	cr_assert_eq(current_config.tab_width, 0);

	yall_config_set_tab_width(5);
	cr_assert_eq(current_config.tab_width, 5);
}

/*
 * O.K.
 * Setter.
 */
Test(config_parameters, test_yall_config_get_tab_width0, .init=test_yall_init, .fini=test_yall_close)
{
	cr_assert_eq(yall_config_get_tab_width(), current_config.tab_width);
	cr_assert_eq(yall_config_get_tab_width(), default_config.tab_width);

	yall_config_set_tab_width(8);
	cr_assert_eq(yall_config_get_tab_width(), 8);

	yall_config_set_tab_width(1);
	cr_assert_eq(yall_config_get_tab_width(), 1);
}

/*
 * O.K.
 * Resetter.
 */
Test(config_parameters, test_yall_config_reset_tab_width0, .init=test_yall_init, .fini=test_yall_close)
{
	yall_config_set_tab_width(6);
	cr_assert_eq(current_config.tab_width, 6);

	yall_config_reset_tab_width();
	cr_assert_eq(current_config.tab_width, default_config.tab_width);
}
