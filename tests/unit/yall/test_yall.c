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

static void tests_yall_setup(void)
{
        _tests_hide_stderr();
}

static void tests_yall_clean(void)
{
        _tests_restore_stderr();
        remove(default_params.file.filename);
}

TestSuite(yall, .init=tests_yall_setup, .fini=tests_yall_clean);

void tests_yall_init_lib(void)
{
        yall_init();
}

void tests_yall_close_lib(void)
{
	yall_close_all();
}

void tests_yall_log_setup(void)
{
        yall_init();
        create_subsystems();
}

void tests_yall_log_clean()
{
        clean_subsystems();

        while (yall_close() != YALL_NOT_INIT);
}

void tests_call_log_function(struct yall_call_data *d, const void *args)
{
	UNUSED(d);
	UNUSED(args);
	
        /*
         * Writing function used in yall_call_log.
         */
}
