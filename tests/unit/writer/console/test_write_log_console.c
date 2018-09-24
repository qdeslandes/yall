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

#include "writer/console/test.h"

/*
 * O.K.
 * Empty string, for each log level
 */
ParameterizedTestParameters(writer_console, test_write_log_console0) {
	return cr_make_param_array(struct param_set_color, ll_and_colors, 8);
}

ParameterizedTest(
	struct param_set_color *p,
	writer_console,
	test_write_log_console0)
{
	cr_assert_eq(YALL_SUCCESS, write_log_console(p->ll, ""));

    #ifdef __linux__
	char output[32] = { 0 };
	snprintf(output, 32, "\033[%dm\033[0m", p->code);

	cr_assert_stderr_eq_str(output);
    #else
    cr_assert(1);
    #endif
}

/*
 * O.K.
 * Non-empty string, for each log level
 */
ParameterizedTestParameters(writer_console, test_write_log_console1) {
	return cr_make_param_array(struct param_set_color, ll_and_colors, 8);
}

ParameterizedTest(
	struct param_set_color *p,
	writer_console,
	test_write_log_console1)
{
	cr_assert_eq(write_log_console(p->ll, "sentence"), YALL_SUCCESS);
	fflush(stderr);

	char output[32] = { 0 };
#ifdef __linux__
	snprintf(output, 32, "\033[%dmsentence\033[0m", p->code);
#elif _WIN32
	snprintf(output, 32, "sentence");
#endif
	cr_assert_stderr_eq_str(output);
}

/*
 * Failing fprintf
 */
Test(writer_console,
	test_write_log_console2)
{
    #ifdef __linux__
	disable_fprintf();
	cr_assert_eq(write_log_console(yall_debug, "nope"), YALL_CONSOLE_WRITE_ERR);
	enable_fprintf();
    #else
    cr_assert(1);
    #endif
}
