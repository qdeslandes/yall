/*
 * Copyright (C) 2017, by Quentin Deslandes
 *
 * This file is part of yall.
 *
 * yall is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * yall is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with yall.  If not, see <http://www.gnu.org/licenses/>.
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
	if (sem_init(&file_sem, 0, 1)) {
		ret = YALL_SEM_INIT_ERR;
		goto end;
	}

	if (sem_init(&console_sem, 0, 1)) {
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
