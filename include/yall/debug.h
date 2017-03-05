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

#ifndef _YALL_DEBUG_H
#define _YALL_DEBUG_H

#ifdef YALL_UNIT
#include <stdio.h>
#include <stdarg.h>

#ifdef __linux__
#	include <semaphore.h>
#elif _WIN32
#	include <Windows.h>
#	include <synchapi.h>
#endif

#define fprintf     _tests_fprintf
#define snprintf    _tests_snprintf
#define vsnprintf   _tests_vsnprintf
#define malloc      _tests_malloc
#define strlen      _tests_strlen

void *_tests_malloc(size_t size);
int _tests_fprintf(FILE *stream, const char *format, ...);
int _tests_snprintf(char *str, size_t size, const char *format, ...);
int _tests_vsnprintf(char *str, size_t size, const char *format, va_list ap);
int _tests_strlen(const char *s);

#ifdef __linux__
#define sem_init    _tests_sem_init
#define sem_wait    _tests_sem_wait
int _tests_sem_init(sem_t *sem, int pshared, unsigned int value);
int _tests_sem_wait(sem_t *sem);
#elif _WIN32
#define CreateMutex _tests_CreateMutex
#define WaitForSingleObject _tests_WaitForSingleObject
HANDLE _tests_CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName);
DWORD _tests_WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
#endif

#endif

#endif