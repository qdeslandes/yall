#include "test_call.h"

Test(call, test_yall_call_add_line0)
{
        struct yall_call_data d = { 0, NULL, NULL };

        // Empty
        yall_config_set_tab_width(2);
        yall_call_add_line(&d, 0, "line");
        cr_assert_str_eq(d.lines->content, "  line\n");
        cr_assert_eq(d.message_size, strlen("  line\n"));

        yall_config_set_tab_width(1);
        yall_call_add_line(&d, 3, "new_line");
        cr_assert_str_eq(d.lines->next->content, "    new_line\n");
        cr_assert_eq(d.message_size, strlen("  line\n") + strlen("    new_line\n"));

        yall_config_set_tab_width(0);
        yall_call_add_line(&d, 1, "test %d %c", 3, 't');
        cr_assert_str_eq(d.lines->next->next->content, "test 3 t\n");
        cr_assert_eq(d.message_size, strlen("  line\n") + strlen("    new_line\n") + strlen("test 3 t\n"));
}
