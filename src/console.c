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

#include "yall/console.h"

#include <stdio.h>
#include <stdint.h>

#ifdef __linux__
#       include <semaphore.h>
#elif _WIN32
#       include <Windows.h>
#endif

#include "yall/utils.h"
#include "yall/errors.h"
#include "yall/debug.h"

#ifdef __linux__
extern sem_t console_sem;
#elif _WIN32
extern HANDLE console_sem;
#endif

#ifdef __linux__
static uint8_t colors[8] = { 97, 92, 92, 93, 91, 91, 91, 91 };

static void set_color(enum yall_log_level log_level)
{
        // Escape sequence is inside its own litteral to get a clearer code.
        fprintf(stderr, "\033" "[%dm", colors[log_level]);
}

static void reset_color(void)
{
        fprintf(stderr, "\033" "[0m");
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
