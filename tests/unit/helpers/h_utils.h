#ifndef _TESTS_HELPERS_UTILS_H
#define _TESTS_HELPERS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#include "yall/yall.h"
#include "yall/message.h"

#ifdef __linux__
#       include <semaphore.h>
#       define NULL_FILE "/dev/null"
#elif _WIN32
#       include <Windows.h>
#       define NULL_FILE "nul"
#endif

#define RETURN_PARAM(type, name) return cr_make_param_array(type, name, sizeof(name)/sizeof(type))

#define TESTS_REDEFINE_LIGHT(function) \
        int function ## _fail = 0; \
        void disable_ ## function() { function ## _fail = 1; } \
        void enable_ ## function() { function ## _fail = 0; }

#define TESTS_REDEFINE(function, fail_code, proto, ...) \
        TESTS_REDEFINE_LIGHT(function) \
        int _tests_ ## function proto \
        { \
                if (function ## _fail) \
                        return fail_code; \
                return function(__VA_ARGS__); \
        }

#define TESTS_REDEFINE_PROTO_LIGHT(function) \
	int  function ## _fail; \
	void disable_ ## function(); \
        void enable_ ## function();

#define TESTS_REDEFINE_PROTO(function, proto) \
        TESTS_REDEFINE_PROTO_LIGHT(function); \
        int _tests_ ## function proto;

void _tests_hide_stderr(void);
void _tests_restore_stderr(void);
void _tests_mutex_init(void);
void _tests_mutex_close(void);

TESTS_REDEFINE_PROTO(snprintf, (char *str, size_t size, const char *format, ...));
TESTS_REDEFINE_PROTO(fprintf, (FILE *stream, const char *format, ...));
TESTS_REDEFINE_PROTO(vsnprintf, (char *str, size_t size, const char *format, va_list arg));
TESTS_REDEFINE_PROTO(strlen, (const char *s));
TESTS_REDEFINE_PROTO(pthread_create, (pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine) (void *), void *arg))

TESTS_REDEFINE_PROTO_LIGHT(malloc);
void *_tests_malloc(size_t size);

#ifdef __linux__
TESTS_REDEFINE_PROTO(sem_wait, (sem_t *sem));
TESTS_REDEFINE_PROTO(sem_init, (sem_t *sem, int pshared, unsigned int value));
#elif _WIN32
TESTS_REDEFINE_PROTO_LIGHT(CreateMutex);
HANDLE test(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName);

TESTS_REDEFINE_PROTO_LIGHT(WaitForSingleObject);
DWORD _tests_WaitForSingleObject( HANDLE hHandle,  DWORD dwMilliseconds);
#endif

#endif
