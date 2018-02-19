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

#include "test_config.h"

extern struct yall_config current_config;
extern struct yall_config default_config;

Test(config, test_yall_config_set_call_header_template0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    yall_config_set_call_header_template("%l %0.4f");
    cr_assert_str_eq(current_config.call_header_template, "%l %0.4f");

    yall_config_set_call_header_template("%sl %0.4f");
    cr_assert_str_eq(current_config.call_header_template, "%sl %0.4f");
}

Test(config, test_yall_config_get_call_header_template0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    cr_assert_str_eq(yall_config_get_call_header_template(), default_config.call_header_template);

    yall_config_set_call_header_template("%l %0.4f");
    cr_assert_str_eq(yall_config_get_call_header_template(), "%l %0.4f");

    yall_config_set_call_header_template("%sl %0.4f");
    cr_assert_str_eq(yall_config_get_call_header_template(), "%sl %0.4f");
}

Test(config, test_yall_config_reset_call_header_template0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    cr_assert_str_eq(yall_config_get_call_header_template(), default_config.call_header_template);
    yall_config_reset_call_header_template();
    cr_assert_str_eq(yall_config_get_call_header_template(), default_config.call_header_template);

    yall_config_set_call_header_template("%l %0.4f");
    yall_config_reset_call_header_template();
    cr_assert_str_eq(current_config.call_header_template, default_config.call_header_template);
}
