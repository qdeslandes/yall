#ifndef _H_YALL_DEBUG
#define _H_YALL_DEBUG

#include <stdio.h>
#include <stdarg.h>
#include <semaphore.h>

#ifdef YALL_COVERAGE
#define fprintf     _tests_fprintf
#define snprintf    _tests_snprintf
#define vsnprintf   _tests_vsnprintf
#define sem_init    _tests_sem_init
#define sem_wait    _tests_sem_wait
#define malloc      _tests_malloc
#define strlen      _tests_strlen

void *_tests_malloc(size_t size);
int _tests_fprintf(FILE *stream, const char *format, ...);
int _tests_snprintf(char *str, size_t size, const char *format, ...);
int _tests_vsnprintf(char *str, size_t size, const char *format, va_list ap);
int _tests_sem_init(sem_t *sem, int pshared, unsigned int value);
int _tests_sem_wait(sem_t *sem);
int _tests_strlen(const char *s);

#endif

#endif
