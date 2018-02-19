/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

    cr_assert_eq(std_matches[0], match_log_level);
    cr_assert_eq(std_matches[1], match_function);
    cr_assert_eq(std_matches[2], match_subsystem);
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
        cr_assert_eq(std_matches[i], match_empty);
}

/*
 * Others
 */
Test(header, test_header_compile_format5)
{
    header_compile_format(std_header, "a%04-faaaa" "bbbbbbbbbb" "cccccccccc" "%pdddddddd" "eeeeeeeeee" "ffffffff%0" "gggggggggg");
    cr_assert_str_eq(std_header_format, "a%04-saaaa" "bbbbbbbbbb" "cccccccccc" "%psddddddd" "eeeeeeeeee" "ffffffff%0" "ggg");

    cr_assert_eq(std_matches[0], match_function);
    cr_assert_eq(std_matches[1], match_date);
    for (int i = 2; i < 10; ++i)
        cr_assert_eq(std_matches[i], 0);
}