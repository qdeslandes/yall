#ifndef _H_YALL_DEBUG
#define _H_YALL_DEBUG

#ifdef YALL_UNIT
#include <stdio.h>
#include <stdarg.h>

#ifdef __linux__
#include <semaphore.h>
#elif _WIN32
#include <Windows.h>
#include <synchapi.h>
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
