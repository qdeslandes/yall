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

ParameterizedTestParameters(writer_console, test_set_color0) {
	return cr_make_param_array(struct param_set_color, ll_and_colors, 8);
}

/*
 * O.K.
 * This is used to changed color on console output are not changed.
 * stderr is redirected, thus, for a given log level, stderr content
 * can be computed and checked.
 */
ParameterizedTest(struct param_set_color *p, writer_console, test_set_color0)
{
	set_color(p->ll);

#ifdef __linux__
	/* Craft the string required */
	char output[32] = { 0 };
	snprintf(output, 32, "\033[%dm", p->code);

	cr_assert_stderr_eq_str(output);
#else
    cr_assert(1);
#endif
}
