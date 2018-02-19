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

Test(call, test_add_line0)
{
        struct yall_call_data d = { 0 };

        add_line(&d, "");
        cr_assert_str_eq(d.lines->content, "");
        cr_assert_eq(d.lines->next, NULL);

        add_line(&d, " ");
        cr_assert_str_eq(d.lines->content, "");
        cr_assert_str_eq(d.lines->next->content, " ");
        cr_assert_eq(d.lines->next->next, NULL);

        add_line(&d, NULL);
        cr_assert_str_eq(d.lines->content, "");
        cr_assert_str_eq(d.lines->next->content, " ");
        cr_assert_eq(d.lines->next->next->content, NULL);
        cr_assert_eq(d.lines->next->next->next, NULL);
}

Test(call, test_add_line1)
{
        struct yall_call_data d = { 0 };

        add_line(&d, "0");
        cr_assert_str_eq(d.lines->content, "0");
        cr_assert_eq(d.lines->next, NULL);
        
        add_line(&d, "572");
        cr_assert_str_eq(d.lines->next->content, "572");
        cr_assert_eq(d.lines->next->next, NULL);
}

Test(call, test_add_line2)
{
        struct yall_call_data d = { 0 };

        add_line(&d, "hello");
        cr_assert_str_eq(d.lines->content, "hello");
        cr_assert_eq(d.lines->next, NULL);

        add_line(&d, "world");
        cr_assert_str_eq(d.lines->next->content, "world");
        cr_assert_eq(d.lines->next->next, NULL);
}
