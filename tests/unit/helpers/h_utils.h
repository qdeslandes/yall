#ifndef _H_TESTS_UTILS
#define _H_TESTS_UTILS

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <semaphore.h>

#define RETURN_PARAM(type, name) return cr_make_param_array(type, name, sizeof(name)/sizeof(type))

/*
 * vsnprintf
 */
#define DISABLE_VSNPRINTF() do{ \
        vsnprintf_fail = true; \
    } while (0)

#define ENABLE_VSNPRINTF() do { \
        vsnprintf_fail = false; \
    } while (0)

extern bool vsnprintf_fail;
int _tests_vsnprintf(char *str, size_t size, const char *format, va_list args);

/*
 * snprintf
 */
#define DISABLE_SNPRINTF() do{ \
        snprintf_fail = true; \
    } while (0)

#define ENABLE_SNPRINTF() do { \
        snprintf_fail = false; \
    } while (0)

extern bool snprintf_fail;
int _tests_snprintf(char *str, size_t size, const char *format, ...);

/*
 * fprintf
 */
#define DISABLE_FPRINTF() do{ \
        fprintf_fail = true; \
    } while (0)

#define ENABLE_FPRINTF() do { \
        fprintf_fail = false; \
    } while (0)

extern bool fprintf_fail;
int _tests_fprintf(FILE *stream, const char *format, ...);

/*
 * sem_wait
 */
#define DISABLE_SEM_WAIT() do{ \
        sem_wait_fail = true; \
    } while (0)

#define ENABLE_SEM_WAIT() do { \
        sem_wait_fail = false; \
    } while (0)

extern bool sem_wait_fail;
int _tests_sem_wait(sem_t *sem);

/*
 * sem_init
 */
#define DISABLE_SEM_INIT() do{ \
        sem_init_fail = true; \
    } while (0)

#define ENABLE_SEM_INIT() do { \
        sem_init_fail = false; \
    } while (0)

extern bool sem_init_fail;
int _tests_sem_init(sem_t *sem, int pshared, unsigned int value);

#endif
