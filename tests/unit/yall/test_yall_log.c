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

#include "test_yall.h"

extern struct yall_subsystem *subsystems;

/*
 * Library not initialized
 */
Test(yall, test_yall_log0)
{
        cr_assert_eq(yall_log("", yall_debug, "", "main.c", 0, ""), YALL_NOT_INIT);
        cr_assert_eq(yall_log("nope", yall_debug, "", "/mnt/main.c", 3, ""), YALL_NOT_INIT);
        cr_assert_eq(yall_log("toolongnameforasubsysteminthelibrary", yall_debug, "", "C:/main.c", 0, ""), YALL_NOT_INIT);
}

/*
 * Empty subsystems list, so using the default subsystem
 */
Test(yall, test_yall_log1, .init=tests_yall_init_lib, .fini=tests_yall_close_lib)
{
        cr_assert_eq(yall_log("", yall_debug, "", "", 0, ""), YALL_LOG_LEVEL_TOO_LOW);
        cr_assert_eq(yall_log("nope", yall_warning, "", "MAIN.c", 0, ""), YALL_SUCCESS);
        cr_assert_eq(yall_log("toolongnameforasubsysteminthelibrary", yall_err, "", "", 43, ""), YALL_SUCCESS);
}

/*
 * Test on getting subsystem and checking log level
 */
TheoryDataPoints(yall, test_yall_log2) = {
        DataPoints(char *, "0", "00", "01", "02", "1", "2", "20", "200", "201", "3"),
        DataPoints(enum yall_log_level, yall_debug, yall_info, yall_notice, yall_warning, yall_err, yall_crit, yall_alert, yall_emerg),
        DataPoints(char *, "toolongnameforafunctionnameinthelibrary", "main", "int main()", "main()", "Class::Method", "int Class::Method", "int Class::Method()"),
	DataPoints(char *, "main.c", "C:/test/code/dev/main.c", "/mnt/storage/Projects/yall/yall.c", "MAIN.C", ""),
	DataPoints(int32_t, 123, 321, 0, 111111, 3, -1, 34),
        DataPoints(char *, "")
};

Theory((char *s, enum yall_log_level ll, char *f, char *F, int32_t line, char *format), yall, test_yall_log2, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        uint8_t waiting_for = YALL_SUCCESS;
        uint8_t ret = yall_log(s, ll, f, F, line, format);
        struct yall_subsystem_params p = { yall_warning, yall_file_output, yall_subsys_enable, "yall_default.log" };
        _get_subsystem(s, subsystems, &p);

        if (ll < p.log_level)
                waiting_for = YALL_LOG_LEVEL_TOO_LOW;

        cr_assert_eq(ret, waiting_for);
}

/*
 * Variadic parameters list
 */
Test(yall, test_yall_log3, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        cr_assert_eq(yall_log("0", yall_emerg, "", "main.c", 0, "%s %d", "hello", 3), YALL_SUCCESS);
        cr_assert_eq(yall_log("3", yall_emerg, "", "", 0, "%X %d", 4, 3), YALL_SUCCESS);
}

/*
 * Disabled subsystem
 */
Test(yall, test_yall_log4, .init=tests_yall_log_setup, .fini=tests_yall_log_clean)
{
        _subsystems[0]->status = yall_subsys_disable;

        cr_assert_eq(yall_log("0", yall_emerg, "", "", 0, ""), YALL_SUBSYS_DISABLED);
}
