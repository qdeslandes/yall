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

#include "yall/file.h"

#include <stdio.h>

#ifdef __linux__
#	include <semaphore.h>
#elif _WIN32
#	include <Windows.h>
#endif

#include "yall/utils.h"
#include "yall/errors.h"

#ifdef __linux__
extern sem_t file_sem;
#elif _WIN32
extern HANDLE file_sem;
#endif

uint8_t write_log_file(const char *file, const char *msg)
{
	uint32_t sem_ret = 0;
	uint8_t ret = YALL_OK;

#ifdef __linux__
	sem_ret = sem_wait(&file_sem);
#elif _WIN32
	sem_ret = WaitForSingleObject(file_sem, INFINITE);
#endif

	if (sem_ret != 0) {
		fprintf(stderr, "DEBUG_YALL - Could not lock file_sem\n");
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

#ifdef __linux__
	sem_post(&file_sem);
#elif _WIN32
	ReleaseMutex(file_sem);
#endif

end:
	return ret;
}
