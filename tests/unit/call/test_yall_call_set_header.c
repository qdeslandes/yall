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