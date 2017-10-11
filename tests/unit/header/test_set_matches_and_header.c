#include "test_header.h"

extern enum yall_matches std_matches[10];
extern enum yall_matches call_matches[10];
extern char std_header_format[10];
extern char call_header_format[10];
extern void set_matches_and_header(enum header_type hdr_type, char **header, enum yall_matches **matches);

/*
 * std_header
 */
Test(header, test_set_matches_and_header0)
{
    char *header = NULL;
    enum yall_matches *matches = NULL;

    set_matches_and_header(std_header, &header, &matches);

    cr_assert_eq(header, std_header_format);
    cr_assert_eq(matches, std_matches);
}

/*
 * call_header
 */
Test(header, test_set_matches_and_header1)
{
    char *header = NULL;
    enum yall_matches *matches = NULL;

    set_matches_and_header(call_header, &header, &matches);

    cr_assert_eq(header, call_header_format);
    cr_assert_eq(matches, call_matches);
}

/*
 * Bad header
 */
Test(header, test_set_matches_and_header2)
{
    char *header = NULL;
    enum yall_matches *matches = NULL;

    set_matches_and_header((enum yall_matches)4, &header, &matches);

    cr_assert_eq(header, std_header_format);
    cr_assert_eq(matches, std_matches);
}