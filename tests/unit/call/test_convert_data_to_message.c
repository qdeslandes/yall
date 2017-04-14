#include "test_call.h"

/*
 * Small buffer
 */
Test(call, test_convert_data_to_messsage0)
{
        /*
        // Without lines
        char buf0[2] = { 0 };
        char *head0 = strdup("Hello, world\n");
        struct yall_call_data d0 = { 13, head0, NULL };

        convert_data_to_message(buf0, 2, &d0);
        cr_assert_str_eq(buf0, "H");

        // Without 1 line
        char buf1[4] = { 0 };
        char *head1 = strdup("Hello, world !\n");
        struct yall_call_data d1 = { 13, head1, NULL };

        struct yall_call_data_line *l0 = malloc(sizeof(struct yall_call_data_line));
        l0->content = strdup("content");
        l0->next = NULL;

        d1.lines = l0;

        convert_data_to_message(buf1, 4, &d1);
        cr_assert_str_eq(buf1, "Hel");
*/
        /*
        // With 2 lines
        char buf2[4] = { 0 };
        char *head2 = strdup("Hello, world !\n");
        struct yall_call_data d2 = { 13, head2, NULL };

        struct yall_call_data_line *l1 = malloc(sizeof(struct yall_call_data_line));
        l1->content = strdup("content ter");
        l1->next = NULL;

        struct yall_call_data_line *l2 = malloc(sizeof(struct yall_call_data_line));
        l2->content = strdup("content bis");
        l2->next = l1;

        d2.lines = l2;

        convert_data_to_message(buf2, 4, &d2);
        cr_assert_str_eq(buf2, "Hel");
        */
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
