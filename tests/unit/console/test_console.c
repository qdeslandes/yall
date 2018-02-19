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

#include "test_console.h"

struct param_set_color ll_and_colors[8] = {
        { yall_debug, 97 },
        { yall_info, 92 },
        { yall_notice, 92 },
        { yall_warning, 93 },
        { yall_err, 91 },
        { yall_crit, 91 },
        { yall_alert, 91 },
        { yall_emerg, 91 }
};

static void tests_console_setup(void)
{
        cr_redirect_stderr();
}

static void tests_console_clean(void)
{

}

TestSuite(console, .init=tests_console_setup, .fini=tests_console_clean);

#ifdef _WIN32
#	include <Windows.h>
#endif

void test_write_log_console_setup(void)
{
}

void test_write_log_console_clean(void)
{
}
