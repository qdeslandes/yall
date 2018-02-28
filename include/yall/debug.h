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
#	include <stdio.h>
#	include <stdarg.h>
#	include <pthread.h>

#	ifdef __linux__
#		include <semaphore.h>
#	elif _WIN32
#		include <Windows.h>
#		include <synchapi.h>
#	endif

#	define fprintf		_tests_fprintf
#	define snprintf		_tests_snprintf
#	define vsnprintf	_tests_vsnprintf
#	define malloc		_tests_malloc
#	define fopen		_tests_fopen
#	define strlen		_tests_strlen
#	define pthread_create	_tests_pthread_create

	void *_tests_malloc(size_t size);
	FILE *_tests_fopen(const char *pathname, const char *mode);
	int _tests_fprintf(FILE *stream, const char *format, ...);
	int _tests_snprintf(char *str, size_t size, const char *format, ...);
	int _tests_vsnprintf(char *str, size_t size, const char *format,
		va_list ap);
	size_t _tests_strlen(const char *s);
	int _tests_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine) (void *), void *arg);

#	ifdef __linux__
#		define sem_init _tests_sem_init
#		define sem_wait _tests_sem_wait
		int _tests_sem_init(sem_t *sem, int pshared,
			unsigned int value);
		int _tests_sem_wait(sem_t *sem);
#	elif _WIN32
#		define CreateMutex _tests_CreateMutex
#		define WaitForSingleObject _tests_WaitForSingleObject
		HANDLE _tests_CreateMutex(
			LPSECURITY_ATTRIBUTES lpMutexAttributes,
			BOOL bInitialOwner, LPCTSTR lpName);
		DWORD _tests_WaitForSingleObject(HANDLE hHandle,
			DWORD dwMilliseconds);
#	endif
#endif

#include <stdbool.h>
#include <stdio.h>

#include "yall/log.h"
#include "yall/yall.h"
#include "yall/error.h"
#include "yall/utils.h"
#include "yall/msvc_defines.h"

/**
 * \brief Enable the debug mode on the library. This function must be called
 *	AFTER yall_init(). Debug message will be wrote using the given
 *	subsystem.
 * \param subsystem Name of the subsystem to us as debug subsystem. If the
 *	subsystem does not exists, no debug message will be generated. Also,
 *	this subsystem should not be modified during debug mode.
 * \return Error code whether it succeed.
 */
_YALL_PUBLIC yall_error yall_enable_debug(const char *subsystem);

/**
 * \brief Disable debug mode. The debug subsystem is not removed nor modified.
 * \return Error code whether it succeed.
 */
_YALL_PUBLIC yall_error yall_disable_debug(void);

/**
 * \brief Return the status of the debug mode.
 * \return Boolean whether the debug mode is initialized.
 */
_YALL_PUBLIC bool yall_is_debug(void);

/**
 * \brief Returns the name of the current debug subsystem.
 * \return Nul-terminated string representing the name of the current debug
 *	subsystem. Returns NULL if the debug mode is disactivated.
 */
const char *debug_subsystem_name(void);

#define _YALL_DBG_EMERG(...) do { \
		if (yall_is_debug()) { \
			_YALL_LOG(debug_subsystem_name(), yall_emerg, \
				##__VA_ARGS__); \
		} \
	} while (0)

#define _YALL_DBG_ALERT(...) do { \
		if (yall_is_debug()) { \
			_YALL_LOG(debug_subsystem_name(), yall_alert, \
				##__VA_ARGS__); \
		} \
	} while (0)

#define _YALL_DBG_CRIT(...) do { \
		if (yall_is_debug()) { \
			_YALL_LOG(debug_subsystem_name(), yall_crit, \
				##__VA_ARGS__); \
		} \
	} while (0)

#define _YALL_DBG_ERR(...) do { \
		if (yall_is_debug()) { \
			_YALL_LOG(debug_subsystem_name(), yall_err, \
				##__VA_ARGS__); \
		} \
	} while (0)

#define _YALL_DBG_WARNING(...) do { \
		if (yall_is_debug()) { \
			_YALL_LOG(debug_subsystem_name(), yall_warning, \
				##__VA_ARGS__); \
		} \
	} while (0)

#define _YALL_DBG_NOTICE(...) do { \
		if (yall_is_debug()) { \
			_YALL_LOG(debug_subsystem_name(), yall_notice, \
				##__VA_ARGS__); \
		} \
	} while (0)

#define _YALL_DBG_INFO(...) do { \
		if (yall_is_debug()) { \
			_YALL_LOG(debug_subsystem_name(), yall_info, \
				##__VA_ARGS__); \
		} \
	} while (0)

#define _YALL_DBG_DEBUG(...) do { \
		if (yall_is_debug()) \
			_YALL_LOG(debug_subsystem_name(), yall_debug, \
				##__VA_ARGS__); { \
		} \
	} while (0)

#define _YALL_CALL_DBG_EMERG(function, args) do { \
		if (yall_is_debug()) { \
			_YALL_CALL_LOG(debug_subsystem_name(), yall_emerg, \
				function, args); \
		} \
	} while (0)

#define _YALL_CALL_DBG_ALERT(function, args) do { \
		if (yall_is_debug()) { \
			_YALL_CALL_LOG(debug_subsystem_name(), yall_alert, \
				function, args); \
		} \
	} while (0)

#define _YALL_CALL_DBG_CRIT(function, args) do { \
		if (yall_is_debug()) { \
			_YALL_CALL_LOG(debug_subsystem_name(), yall_crit, \
				function, args); \
		} \
	} while (0)

#define _YALL_CALL_DBG_ERR(function, args) do { \
		if (yall_is_debug()) { \
			_YALL_CALL_LOG(debug_subsystem_name(), yall_err, \
				function, args); \
		} \
	} while (0)

#define _YALL_CALL_DBG_WARNING(function, args) do { \
		if (yall_is_debug()) { \
			_YALL_CALL_LOG(debug_subsystem_name(), yall_warning, \
				function, args); \
		} \
	} while (0)

#define _YALL_CALL_DBG_NOTICE(function, args) do { \
		if (yall_is_debug()) { \
			_YALL_CALL_LOG(debug_subsystem_name(), yall_notice, \
				function, args); \
		} \
	} while (0)

#define _YALL_CALL_DBG_INFO(function, args) do { \
		if (yall_is_debug()) { \
			_YALL_CALL_LOG(debug_subsystem_name(), yall_info, \
				function, args); \
		} \
	} while (0)

#define _YALL_CALL_DBG_DEBUG(function, args) do { \
		if (yall_is_debug()) \
			_YALL_CALL_LOG(debug_subsystem_name(), yall_debug, \
				function, args); { \
		} \
	} while (0)

#endif
