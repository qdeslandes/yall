#include "test_call.h"

Test(call, test_yall_call_add_line0)
{
        struct yall_call_data d = { 0, NULL, NULL };

        // Empty
        yall_call_add_line(&d, 0, "line");
        cr_assert_str_eq(d.lines->content, "\tline\n");
        cr_assert_eq(d.message_size, strlen("\tline\n"));

        yall_call_add_line(&d, 3, "new_line");
        cr_assert_str_eq(d.lines->next->content, "\t\t\t\tnew_line\n");
        cr_assert_eq(d.message_size, 6 + strlen("\t\t\t\tnew_line\n"));

        yall_call_add_line(&d, 1, "test %d %c", 3, 't');
        cr_assert_str_eq(d.lines->next->next->content, "\t\ttest 3 t\n");
        cr_assert_eq(d.message_size, 19 + strlen("\t\ttest 3 t\n"));
}
