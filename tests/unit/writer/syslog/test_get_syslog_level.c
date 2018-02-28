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

#include "writer/test_writer.h"

#ifdef __linux__
#include <syslog.h>

extern int get_syslog_level(enum yall_log_level ll);

Test(writer_syslog, test_get_syslog_level0)
{
	cr_assert_eq(get_syslog_level(yall_debug), LOG_DEBUG);
	cr_assert_eq(get_syslog_level(yall_info), LOG_INFO);
	cr_assert_eq(get_syslog_level(yall_notice), LOG_NOTICE);
	cr_assert_eq(get_syslog_level(yall_warning), LOG_WARNING);
	cr_assert_eq(get_syslog_level(yall_err), LOG_ERR);
	cr_assert_eq(get_syslog_level(yall_crit), LOG_CRIT);
	cr_assert_eq(get_syslog_level(yall_alert), LOG_ALERT);
}

#endif
