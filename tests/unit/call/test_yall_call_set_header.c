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

#include "test_call.h"

/*
 * Add a header for the first time
 */
Test(call, test_yall_call_set_header0)
{
        struct yall_call_data d = { 1, NULL, NULL };
                d.header = malloc(DEFAULT_LINE_SIZE);
                d.header[0] = '\n';
                d.header[1] = 0;

        yall_call_set_header(&d, "header");
        cr_assert_str_eq(d.header, "header\n");

        yall_call_set_header(&d, "header %c %d", 't', 3);
        cr_assert_str_eq(d.header, "header t 3\n");

        free(d.header);
}

/*
 * Replace an-existing header
 */
Test(call, test_yall_call_set_header1)
{
        char *tmp = malloc(DEFAULT_LINE_SIZE);
        strcpy(tmp, "hello");
        struct yall_call_data d = { 0, tmp, NULL };

        yall_call_set_header(&d, "header");
        cr_assert_str_eq(d.header, "header\n");

        yall_call_set_header(&d, "header %c %d", 't', 3);
        cr_assert_str_eq(d.header, "header t 3\n");

        free(d.header);
}
