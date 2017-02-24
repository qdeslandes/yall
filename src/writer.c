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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/writer.h"

#ifdef __linux__
#	include <semaphore.h>
#elif _WIN32
#	include <Windows.h>
#endif

#include "yall/utils.h"
#include "yall/errors.h"
#include "yall/console.h"
#include "yall/file.h"

#ifdef __linux__
sem_t file_sem;
sem_t console_sem;
#elif _WIN32
HANDLE file_sem = NULL;
HANDLE console_sem = NULL;
#endif

uint8_t writer_init(void)
{
	uint8_t ret = YALL_OK;

#ifdef __linux__
	if (sem_init(&file_sem, 0, 1) || sem_init(&console_sem, 0, 1)) {
		ret = YALL_SEM_INIT_ERR;
		goto end;
	}
#elif _WIN32
	if ((file_sem = CreateMutex(NULL, FALSE, NULL)) == NULL) {
		ret = YALL_SEM_INIT_ERR;
		goto end;
	}

	if ((console_sem = CreateMutex(NULL, FALSE, NULL)) == NULL) {
		ret = YALL_SEM_INIT_ERR;
		goto end;
	}
#endif

end:
	return ret;
}

uint8_t write_msg(enum yall_output_type output_type,
	enum yall_log_level log_level,
	const char *output_file,
	const char *msg)
{
	uint8_t ret = YALL_OK;

	if (yall_console_output & output_type)
		ret = write_log_console(log_level, msg);

	if (yall_file_output & output_type)
		ret = write_log_file(output_file, msg);

	return ret;
}

void writer_close(void)
{
	/*
	 * Closing an invalid semaphore is okay, but closing an invalid HANDLE
	 * will fuck this thing up. So we need to check that...
	 */
#ifdef __linux__
	sem_destroy(&file_sem);
	sem_destroy(&console_sem);
#elif _WIN32
	if (file_sem)
		CloseHandle(file_sem);

	if (console_sem)
		CloseHandle(console_sem);

	file_sem = NULL;
	console_sem = NULL;
#endif
}
