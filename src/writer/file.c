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

#include "yall/writer/file.h"

#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "yall/utils.h"
#include "yall/debug.h"

yall_error write_log_file(const char *file, const char *msg)
{
	uint32_t sem_ret = 0;
	yall_error ret = YALL_SUCCESS;

	if (sem_ret != 0) {
		ret = YALL_FILE_LOCK_ERR;
		goto end;
	}

	FILE *f = fopen(file, "a");

	if (f) {
		fprintf(f, "%s", msg);
		fclose(f);
	} else {
		ret = YALL_FILE_OPEN_ERR;
	}

end:
	return ret;
}

void delete_old_log_file(const char *filepath)
{
	remove(filepath);
}
