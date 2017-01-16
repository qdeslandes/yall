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

#include "yall/console.h"

#include <stdio.h>
#include <stdint.h>

#ifdef __linux__
#	include <semaphore.h>
#elif _WIN32
#	include <Windows.h>
#endif

#include "yall/utils.h"
#include "yall/errors.h"

#ifdef __linux__
extern sem_t console_sem;
#elif _WIN32
extern HANDLE console_sem;
#endif

#ifdef __linux__
static uint8_t colors[8] = { 97, 92, 92, 93, 91, 91, 91, 91 };

static void set_color(enum yall_log_level log_level)
{
	fprintf(stderr, "\033[%dm", colors[log_level]);
}

static void reset_color(void)
{
	fprintf(stderr, "\033[0m");
}
#elif _WIN32
static uint8_t colors[8] = { 15, 10, 10, 14, 12, 12, 12, 12 };

static void set_color(enum yall_log_level log_level)
{
	WORD wColor;
	int color = colors[log_level];
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

static void reset_color(void)
{
	WORD wColor;
	int color = 15;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}
#endif

uint8_t write_log_console(enum yall_log_level log_level,
	const char *msg)
{
	uint32_t sem_ret = 0;
	uint8_t ret = YALL_OK;

#ifdef __linux__
	sem_ret = sem_wait(&console_sem);
#elif _WIN32
	sem_ret = WaitForSingleObject(console_sem, INFINITE);
#endif

	if (sem_ret != 0) {
		fprintf(stderr, "DEBUG_YALL - Could not lock console_sem\n");
		ret = YALL_CONSOLE_LOCK_ERR;
		goto end;
	}

	set_color(log_level);

	if (fprintf(stderr, msg) < 0)
		ret = YALL_CONSOLE_WRITE_ERR;

	reset_color();

#ifdef __linux__
	sem_post(&console_sem);
#elif _WIN32
	ReleaseMutex(console_sem);
#endif

end:
	return ret;
}
