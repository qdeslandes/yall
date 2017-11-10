#include "test_header.h"

extern enum yall_matches std_matches[10];
extern char std_header_format[64];

/*
 * Empty
 */
Test(header, test_header_compile_format0)
{
    header_compile_format(std_header, "");
    cr_assert_str_eq(std_header_format, "");

    for (int i = 0; i < 10; ++i)
        cr_assert_eq(std_matches[i], 0);
}

/*
 * Short without modifiers
 */
Test(header, test_header_compile_format1)
{
    header_compile_format(std_header, "foo bar foo bar");
    cr_assert_str_eq(std_header_format, "foo bar foo bar");

    for (int i = 0; i < 10; ++i)
        cr_assert_eq(std_matches[i], 0);
}

/*
 * Short with modifiers
 */
Test(header, test_header_compile_format2)
{
    header_compile_format(std_header, "%04l %05f :: %s :: -> ");
    cr_assert_str_eq(std_header_format, "%04s %05s :: %s :: -> ");

    cr_assert_eq(std_matches[0], log_level);
    cr_assert_eq(std_matches[1], function);
    cr_assert_eq(std_matches[2], subsystem);
    for (int i = 3; i < 10; ++i)
        cr_assert_eq(std_matches[i], 0);
}

/*
 * Too long
 */
Test(header, test_header_compile_format3)
{
    header_compile_format(std_header, "aaaaaaaaaa" "bbbbbbbbbb" "cccccccccc" "dddddddddd" "eeeeeeeeee" "ffffffffff" "gggggggggg");
    cr_assert_str_eq(std_header_format, "aaaaaaaaaa" "bbbbbbbbbb" "cccccccccc" "dddddddddd" "eeeeeeeeee" "ffffffffff" "ggg");

    for (int i = 0; i < 10; ++i)
        cr_assert_eq(std_matches[i], 0);
}

/*
 * Others
 */
Test(header, test_header_compile_format5)
{
    header_compile_format(std_header, "a%04-faaaa" "bbbbbbbbbb" "cccccccccc" "%pdddddddd" "eeeeeeeeee" "ffffffff%0" "gggggggggg");
    cr_assert_str_eq(std_header_format, "a%04-saaaa" "bbbbbbbbbb" "cccccccccc" "%psddddddd" "eeeeeeeeee" "ffffffff%0" "ggg");

    cr_assert_eq(std_matches[0], function);
    cr_assert_eq(std_matches[1], date);
    for (int i = 2; i < 10; ++i)
        cr_assert_eq(std_matches[i], 0);
}