#include "h_utils.h"

#include <stdarg.h>

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
