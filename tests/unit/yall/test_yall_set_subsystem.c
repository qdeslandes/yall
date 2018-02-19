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

#include "test_yall.h"

extern struct yall_subsystem *subsystems;

/*
 * Library not initialized
 */
Test(yall, test_yall_set_subsystem0)
{
        cr_assert_eq(yall_set_subsystem(NULL, NULL, yall_debug, yall_console_output, NULL), YALL_NOT_INIT);
}

/*
 * Bad name
 */
Test(yall, test_yall_set_subsystem1, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        cr_assert_eq(yall_set_subsystem(NULL, NULL, yall_debug, yall_console_output, NULL), YALL_NO_NAME);
}

/*
 * Need to update an existing subsystem
 */
Test(yall, test_yall_set_subsystem2, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        cr_assert_eq(yall_set_subsystem("0", NULL, yall_debug, yall_console_output, NULL), YALL_SUCCESS);
}

/*
 * Need to create a subsystem
 */
Test(yall, test_yall_set_subsystem3, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        cr_assert_eq(yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL), YALL_SUCCESS);
}