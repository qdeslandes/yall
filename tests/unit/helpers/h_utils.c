#include "h_utils.h"

bool vsnprintf_fail = false;
int _tests_vsnprintf(char *str, size_t size, const char *format, va_list args)
{
    if (vsnprintf_fail)
        return -1;

    return vsnprintf(str, size, format, args);
}

bool snprintf_fail = false;
int _tests_snprintf(char *str, size_t size, const char *format, ...)
{
    if (snprintf_fail)
        return -1;

    va_list args;
    va_start(args, format);

    return vsnprintf(str, size, format, args);
}

bool fprintf_fail = false;
int _tests_fprintf(FILE *stream, const char *format, ...)
{
    if (fprintf_fail)
        return -1;

    va_list args;
    va_start(args, format);

    return vfprintf(stream, format, args);
}

bool sem_wait_fail = false;
int _tests_sem_wait(sem_t *sem)
{
    if (sem_wait_fail)
        return -1;
    return sem_wait(sem);
}
