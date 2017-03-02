#include "h_utils.h"

#ifdef __linux__
#include <semaphore.h>
extern sem_t console_sem;
extern sem_t file_sem;
#elif _WIN32
#include <Windows.h>
extern HANDLE console_sem;
extern HANDLE file_sem;
#endif

void _tests_mutex_init(void)
{
#ifdef __linux__
	sem_init(&console_sem, 0, 1);
	sem_init(&file_sem, 0, 1);
#elif _WIN32
	console_sem = CreateMutex(NULL, FALSE, NULL);
	file_sem = CreateMutex(NULL, FALSE, NULL);
#endif
}

void _tests_mutex_close(void)
{
#ifdef __linux__
	sem_destroy(&console_sem);
	sem_destroy(&file_sem);
#elif _WIN32
	CloseHandle(console_sem);
	CloseHandle(file_sem);
#endif
}

TESTS_REDEFINE_LIGHT(snprintf);
int _tests_snprintf(char *str, size_t size, const char *format, ...)
{
	if (snprintf_fail)
		return -1;

	va_list args;
	va_start(args, format);

	return vsnprintf(str, size, format, args);
}

TESTS_REDEFINE_LIGHT(fprintf);
int _tests_fprintf(FILE *stream, const char *format, ...)
{
	if (fprintf_fail)
		return -1;

	va_list args;
	va_start(args, format);

	return vfprintf(stream, format, args);
}

TESTS_REDEFINE_LIGHT(malloc);
void *_tests_malloc(size_t size)
{
	if (malloc_fail)
		return NULL;

	return malloc(size);
}

TESTS_REDEFINE(vsnprintf, -1, (char *str, size_t size, const char *format, va_list args), str, size, format, args);
TESTS_REDEFINE(strlen, -2, (const char *str), str);

#ifdef __linux__
TESTS_REDEFINE(sem_wait, -1, (sem_t *sem), sem);
TESTS_REDEFINE(sem_init, -1, (sem_t *sem, int pshared, unsigned int value), sem, pshared, value);
#elif _WIN32
#endif
