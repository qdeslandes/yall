#include "test_call.h"

void add_line(struct yall_call_data *d, const char *content);

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
