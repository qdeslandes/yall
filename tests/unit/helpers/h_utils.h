#ifndef _H_TESTS_UTILS
#define _H_TESTS_UTILS

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>

#define RETURN_PARAM(type, name) return cr_make_param_array(type, name, sizeof(name)/sizeof(type))

#define REDEF_LIGHT(function, fail_code) \
	uint8_t function ## _fail = 0; \
	void disable_ ## function() { function ## _fail = 1; } \
	void enable_ ## function() { function ## _fail = 0; } \
	void set_ ## function(uint8_t v) { function ## _fail = v; }

#define REDEF(function, fail_code, proto, ...) \
    REDEF_LIGHT(function, proto) \
	uint8_t _tests_ ## function proto \
	{ \
		if (function ## _fail) \
			return fail_code; \
		return function(__VA_ARGS__); \
	} \

#define REDEF_PROTO(function, proto) \
	extern uint8_t  function ## _fail; \
	uint8_t _tests_ ## function proto; \
	void disable_ ## function(); \
	void enable_ ## function(); \
	void set_ ## function(uint8_t v)

REDEF_PROTO(snprintf, (char *str, size_t size, const char *format, ...));
REDEF_PROTO(fprintf, (FILE *stream, const char *format, ...));
REDEF_PROTO(vsnprintf, (char *str, size_t size, const char *format, va_list arg));
REDEF_PROTO(sem_wait, (sem_t *sem));
REDEF_PROTO(sem_init, (sem_t *sem, int pshared, unsigned int value));

#endif
