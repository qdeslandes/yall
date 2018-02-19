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
 * Small buffer
 */
Test(call, test_convert_data_to_messsage0)
{
        // Without lines
        char buf0[2] = { 0 };
        char *head0 = strdup("Hello, world\n");
        struct yall_call_data d0 = { 13, head0, NULL };

        convert_data_to_message(buf0, 2, &d0);
        cr_assert_str_eq(buf0, "H");

        // Without 1 line
        char buf1[4] = { 0 };
        char *head1 = strdup("Hello, world !\n");
        struct yall_call_data d1 = { 22, head1, NULL };

        struct yall_call_data_line *l0 = malloc(sizeof(struct yall_call_data_line));
        l0->content = strdup("content");
        l0->next = NULL;

        d1.lines = l0;

        convert_data_to_message(buf1, 4, &d1);
        cr_assert_str_eq(buf1, "Hel");

        // With 2 lines
        char buf2[4] = { 0 };
        char *head2 = strdup("Hello, world !\n");
        struct yall_call_data d2 = { 35, head2, NULL };

        struct yall_call_data_line *l1 = malloc(sizeof(struct yall_call_data_line));
        l1->content = strdup("content ter");
        l1->next = NULL;

        struct yall_call_data_line *l2 = malloc(sizeof(struct yall_call_data_line));
        l2->content = strdup("content bis");
        l2->next = l1;

        d2.lines = l2;

        convert_data_to_message(buf2, 4, &d2);
        cr_assert_str_eq(buf2, "Hel");
}

/*
 * Correct size buffer
 */
Test(call, test_convert_data_to_messsage1)
{
        // Without lines
        char buf0[20] = { 0 };
        char *head0 = strdup("Hello, world\n");
        struct yall_call_data d0 = { 13, head0, NULL };

        convert_data_to_message(buf0, 20, &d0);
        cr_assert_str_eq(buf0, "Hello, world\n");

        // Without 1 line
        char buf1[40] = { 0 };
        char *head1 = strdup("Hello, world !\n");
        struct yall_call_data d1 = { 13, head1, NULL };

        struct yall_call_data_line *l0 = malloc(sizeof(struct yall_call_data_line));
        l0->content = strdup("content");
        l0->next = NULL;

        d1.lines = l0;

        convert_data_to_message(buf1, 40, &d1);
        cr_assert_str_eq(buf1, "Hello, world !\ncontent");

        // With 2 lines
        char buf2[40] = { 0 };
        char *head2 = strdup("Hello, world !\n");
        struct yall_call_data d2 = { 13, head2, NULL };

        struct yall_call_data_line *l1 = malloc(sizeof(struct yall_call_data_line));
        l1->content = strdup("content ter");
        l1->next = NULL;

        struct yall_call_data_line *l2 = malloc(sizeof(struct yall_call_data_line));
        l2->content = strdup("content bis");
        l2->next = l1;

        d2.lines = l2;

        convert_data_to_message(buf2, 40, &d2);
        cr_assert_str_eq(buf2, "Hello, world !\ncontent biscontent ter");
}
