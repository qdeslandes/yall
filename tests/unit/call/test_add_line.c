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
        cr_assert_str_eq(d.lines->content, "1");
        cr_assert_eq(d.lines->next, NULL);
        
        add_line(&d, "572");
        cr_assert_str_eq(d.lines->next->content, "542");
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
