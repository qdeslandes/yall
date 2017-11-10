#include "test_header.h"

extern void set_date(char *date);

Test(header, test_set_date0)
{
    char date[YALL_DATE_LONG_LEN] = { 0 };

    set_date(date);

    cr_assert_eq(date[YALL_DATE_LONG_LEN - 1], '\0');
}