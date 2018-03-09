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

#include "log_level/test.h"

/*
 * O.K.
 */
Test(log_level, test_log_level_to_pretty_str0)
{
	cr_assert_str_eq(log_level_to_pretty_str(yall_debug), "DEBUG");
	cr_assert_str_eq(log_level_to_pretty_str(yall_info), "INFO");
	cr_assert_str_eq(log_level_to_pretty_str(yall_notice), "NOTICE");
	cr_assert_str_eq(log_level_to_pretty_str(yall_warning), "WARNING");
	cr_assert_str_eq(log_level_to_pretty_str(yall_err), "ERROR");
	cr_assert_str_eq(log_level_to_pretty_str(yall_crit), "CRITICAL");
	cr_assert_str_eq(log_level_to_pretty_str(yall_alert), "ALERT");
	cr_assert_str_eq(log_level_to_pretty_str(yall_emerg), "EMERGENCY");
}
