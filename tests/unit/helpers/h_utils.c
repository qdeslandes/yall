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

#include "helpers/h_utils.h"

#include <fcntl.h>

#ifdef __linux__
#include <semaphore.h>
#include <unistd.h>
#elif _WIN32
#include <Windows.h>
#include <io.h>

#define dup _dup
#define dup2 _dup2
#define fileno _fileno
#define open _open
#define close _close
#define O_RDWR _O_RDWR
#endif

static int old_stderr;
static int tmp_fd;

void _tests_hide_stderr(void)
{
        tmp_fd = open(NULL_FILE, O_RDWR);
        old_stderr = dup(fileno(stderr));
        dup2(tmp_fd, fileno(stderr));
}

void _tests_restore_stderr(void)
{
        dup2(old_stderr, fileno(stderr));
        close(tmp_fd);
}

void _tests_mutex_init(void)
{
}

void _tests_mutex_close(void)
{
}

TESTS_REDEFINE_LIGHT(snprintf)
int _tests_snprintf(char *str, size_t size, const char *format, ...)
{
        if (snprintf_fail)
                return -1;

        va_list args;
        va_start(args, format);

        return vsnprintf(str, size, format, args);
}

TESTS_REDEFINE_LIGHT(fprintf)
int _tests_fprintf(FILE *stream, const char *format, ...)
{
        if (fprintf_fail)
                return -1;

        va_list args;
        va_start(args, format);

        return vfprintf(stream, format, args);
}

TESTS_REDEFINE_LIGHT(malloc)
void *_tests_malloc(size_t size)
{
        if (malloc_fail)
                return NULL;

        return malloc(size);
}

TESTS_REDEFINE_LIGHT(fopen)
FILE *_tests_fopen(const char *pathname, const char *mode)
{
	if (fopen_fail)
		return NULL;
	
	return fopen(pathname, mode);
}

TESTS_REDEFINE(vsnprintf, -1, (char *str, size_t size, const char *format, va_list args), str, size, format, args)
TESTS_REDEFINE(strlen, -2, (const char *str), str)
TESTS_REDEFINE(pthread_create, -1, (pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine) (void *), void *arg), thread, attr, start_routine, arg)

#ifdef __linux__
TESTS_REDEFINE(sem_wait, -1, (sem_t *sem), sem)
TESTS_REDEFINE(sem_init, -1, (sem_t *sem, int pshared, unsigned int value), sem, pshared, value)
#elif _WIN32
TESTS_REDEFINE_LIGHT(CreateMutex)
HANDLE _tests_CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName)
{
        if (CreateMutex_fail)
                return NULL;

        return CreateMutex(lpMutexAttributes, bInitialOwner, lpName);
}

TESTS_REDEFINE_LIGHT(WaitForSingleObject)
DWORD _tests_WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)
{
        if (WaitForSingleObject_fail)
                return 1;

        return WaitForSingleObject(hHandle, dwMilliseconds);
}
#endif
