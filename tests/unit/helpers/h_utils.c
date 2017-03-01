#include "h_utils.h"

extern sem_t console_sem;
extern sem_t file_sem;

void _tests_mutex_init(void)
{
        sem_init(&console_sem, 0, 1);
        sem_init(&file_sem, 0, 1);
}

void _tests_mutex_close(void)
{
        sem_destroy(&console_sem);
        sem_destroy(&file_sem);
}

REDEF_LIGHT(snprintf, -1);
int _tests_snprintf(char *str, size_t size, const char *format, ...)
{
    if (snprintf_fail)
        return -1;

    va_list args;
    va_start(args, format);

    return vsnprintf(str, size, format, args);
}

REDEF_LIGHT(fprintf, -1);
int _tests_fprintf(FILE *stream, const char *format, ...)
{
    if (fprintf_fail)
        return -1;

    va_list args;
    va_start(args, format);

    return vfprintf(stream, format, args);
}

REDEF(vsnprintf, -1, (char *str, size_t size, const char *format, va_list args), str, size, format, args);
REDEF(sem_wait, -1, (sem_t *sem), sem);
REDEF(sem_init, -1, (sem_t *sem, int pshared, unsigned int value), sem, pshared, value);
REDEF(malloc, NULL, (size_t size), size);
