#include "test_call.h"

struct yall_call_data_line *remove_first_line(struct yall_call_data *d);

/*
 * Empty lines set
 */
Test(call, test_remove_first_line0)
{
        struct yall_call_data d = { 0, "", NULL };

        cr_assert_eq(remove_first_line(&d), NULL);
}

/*
 * Non-empty lines set
 */
Test(call, test_remove_first_liner1)
{
        struct yall_call_data d = { 3, "", NULL };

        struct yall_call_data_line l = { "2", NULL };
        struct yall_call_data_line m = { "1", &l };
        struct yall_call_data_line n = { "0", &m };
        d.lines = &n;

        cr_assert_eq(remove_first_line(&d), &n);
        cr_assert_eq(d.message_size, 2);

        cr_assert_eq(remove_first_line(&d), &m);
        cr_assert_eq(d.message_size, 1);

        cr_assert_eq(remove_first_line(&d), &l);
        cr_assert_eq(d.message_size, 0);
}
