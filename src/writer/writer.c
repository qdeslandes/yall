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

#include "yall/writer/writer.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include "yall/error.h"
#include "yall/writer/thread.h"
#include "yall/utils.h"
#include "yall/errors.h"
#include "yall/writer/console.h"
#include "yall/writer/file.h"
#include "yall/debug.h"

uint8_t writer_init(uint16_t frequency)
{
	yall_error ret = YALL_SUCCESS;

	ret = start_thread(frequency);

	return ret;
}

yall_error write_msg(enum yall_output_type output_type,
	enum yall_log_level log_level,
	const char *output_file,
	const char *msg)
{
	yall_error ret = YALL_SUCCESS;

	if (yall_console_output & output_type)
		ret = write_log_console(log_level, msg);

	if (yall_file_output & output_type)
		ret = write_log_file(output_file, msg);

	return ret;
}

void writer_close(void)
{
	stop_thread();
}
