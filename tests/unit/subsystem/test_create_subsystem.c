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

#include "test_subsystem.h"

/*
 * Test parameters combination
 */
TheoryDataPoints(subsystem, test_create_subsystem0) = {
        DataPoints(char *, "short", "middlename", "toolongnameforasubsystemidkwhattodowiththat"),
        DataPoints(enum yall_log_level, yall_debug, yall_info, yall_notice, yall_warning, yall_err, yall_crit, yall_alert, yall_emerg),
        DataPoints(enum yall_output_type, yall_console_output, yall_file_output, yall_inherited_output),
        DataPoints(char *, "log.log")
};

Theory((char *n, enum yall_log_level ll, enum yall_output_type ot, char *of), subsystem, test_create_subsystem0)
{
        char subsys_name[SUBSYS_NAME_LEN] = { 0 };
        strncpy(subsys_name, n, SUBSYS_NAME_LEN - 1);

        struct yall_subsystem *s = create_subsystem(n, ll, ot, of);

        cr_assert(s);
        cr_assert_eq(s->parent, NULL);
        cr_assert_eq(s->childs, NULL);
        cr_assert_eq(s->previous, NULL);
        cr_assert_eq(s->next, NULL);
        cr_assert_str_eq(s->name, subsys_name);
        cr_assert_eq(s->log_level, ll);
        cr_assert_eq(s->output_type, ot);
        cr_assert_str_eq(s->file.filename, of);
}