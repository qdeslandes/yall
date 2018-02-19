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

#include "test_debug.h"

extern uint16_t initialized;
extern bool debug;
extern const char *debug_subsystem;

/*
 *Library not initialized
 */
Test(debug, test_yall_disable_debug0)
{
        cr_assert_eq(debug, false);
        
        cr_assert_eq(yall_disable_debug(), YALL_NOT_INIT);

        cr_assert_eq(debug, false);
}

/*
 * Multiple disabling
 */
Test(debug, test_yall_disable_debug1)
{
        cr_assert_eq(debug, false);

        yall_init();
        yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);
        yall_enable_debug("test");
        
        cr_assert_eq(debug, true);

        yall_disable_debug();
        cr_assert_eq(debug, false);
        cr_assert_eq(debug_subsystem, NULL);
        yall_disable_debug();
        cr_assert_eq(debug, false);
        cr_assert_eq(debug_subsystem, NULL);
}