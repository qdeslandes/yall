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

#ifndef _YALL_DEBUG_H
#define _YALL_DEBUG_H


#ifdef YALL_UNIT
#       include <stdio.h>
#       include <stdarg.h>

#       ifdef __linux__
#	      include <semaphore.h>
#       elif _WIN32
#	      include <Windows.h>
#	      include <synchapi.h>
#       endif

#       define fprintf     _tests_fprintf
#       define snprintf    _tests_snprintf
#       define vsnprintf   _tests_vsnprintf
#       define malloc      _tests_malloc
#       define strlen      _tests_strlen
#	define pthread_create _tests_pthread_create

	void *_tests_malloc(size_t size);
	int _tests_fprintf(FILE *stream, const char *format, ...);
	int _tests_snprintf(char *str, size_t size, const char *format, ...);
	int _tests_vsnprintf(char *str, size_t size, const char *format,
		va_list ap);
	size_t _tests_strlen(const char *s);
	int _tests_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine) (void *), void *arg);

#       ifdef __linux__
#	       define sem_init    _tests_sem_init
#	       define sem_wait    _tests_sem_wait
		int _tests_sem_init(sem_t *sem, int pshared,
			unsigned int value);
		int _tests_sem_wait(sem_t *sem);
#       elif _WIN32
#	       define CreateMutex _tests_CreateMutex
#	       define WaitForSingleObject _tests_WaitForSingleObject
		HANDLE _tests_CreateMutex(
			LPSECURITY_ATTRIBUTES lpMutexAttributes,
			BOOL bInitialOwner, LPCTSTR lpName);
		DWORD _tests_WaitForSingleObject(HANDLE hHandle,
			DWORD dwMilliseconds);
#       endif
#endif

#include <stdbool.h>

#include "yall/yall.h"
#include "yall/utils.h"
#include "yall/msvc_defines.h"

/*
 * yall_enable_debug : enable the debug mode on the library. This
 *      function must be called AFTER yall_init().
 */
_YALL_PUBLIC void yall_enable_debug(void);

/*
 * yall_disable_debug : disable the debug mode.
 */
_YALL_PUBLIC void yall_disable_debug(void);

/*
 * yall_is_debug : return the debug mode status.
 */
_YALL_PUBLIC bool yall_is_debug(void);

#ifdef DEBUG

#       include <stdio.h>
#       include "yall/log.h"

#       define _YALL_DBG_EMERG(...) do { \
			if (yall_is_debug()) { \
				_YALL_LOG("yall", yall_emerg, ##__VA_ARGS__); \
			} \
		} while (0)
#       define _YALL_DBG_ALERT(...) do { \
			if (yall_is_debug()) { \
				_YALL_LOG("yall", yall_alert, ##__VA_ARGS__); \
			} \
		} while (0)
#       define _YALL_DBG_CRIT(...) do { \
			if (yall_is_debug()) { \
				_YALL_LOG("yall", yall_crit, ##__VA_ARGS__); \
			} \
		} while (0)
#       define _YALL_DBG_ERR(...) do { \
			if (yall_is_debug()) { \
				_YALL_LOG("yall", yall_err, ##__VA_ARGS__); \
			} \
		} while (0)
#       define _YALL_DBG_WARNING(...) do { \
			if (yall_is_debug()) { \
				_YALL_LOG("yall", yall_warning, \
					##__VA_ARGS__); \
			} \
		} while (0)
#       define _YALL_DBG_NOTICE(...) do { \
			if (yall_is_debug()) { \
				_YALL_LOG("yall", yall_notice, ##__VA_ARGS__); \
			} \
		} while (0)
#       define _YALL_DBG_INFO(...) do { \
			if (yall_is_debug()) { \
				_YALL_LOG("yall", yall_info, ##__VA_ARGS__); \
			} \
		} while (0)
#       define _YALL_DBG_DEBUG(...) do { \
			if (yall_is_debug()) \
				_YALL_LOG("yall", yall_debug, \
					##__VA_ARGS__); { \
			} \
		} while (0)
#else

#       define _YALL_DBG_EMERG(...)
#       define _YALL_DBG_ALERT(...)
#       define _YALL_DBG_CRIT(...)
#       define _YALL_DBG_ERR(...)
#       define _YALL_DBG_WARNING(...)
#       define _YALL_DBG_NOTICE(...)
#       define _YALL_DBG_INFO(...)
#       define _YALL_DBG_DEBUG(...)

#endif

#endif
