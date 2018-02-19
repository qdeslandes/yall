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

#include "test_message.h"

#include <stdarg.h>

static void tests_message_setup(void)
{
	yall_init();
}

static void tests_message_clean(void)
{
	yall_close_all();
}

TestSuite(message, .init=tests_message_setup, .fini=tests_message_clean);

/*
 * We can't create a va_list from scratch. So, to test generate_message(),
 * we create a wrapper variadic function which create a va_list from its
 * arguments.
 */
size_t std_wrapper(char *log_buffer, size_t len, const char *message_format, ...)
{
	UNUSED(log_buffer);
	UNUSED(len);

	size_t _len = 0;
        va_list args;
        va_start(args, message_format);

	//_len = generate_std_msg(log_buffer, len, message_format, args);

	va_end(args);

	return _len;
}

