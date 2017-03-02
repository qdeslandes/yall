#ifndef _H_TESTS_UTILS
#define _H_TESTS_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "yall/yall.h"
#include "yall/message.h"

#define RETURN_PARAM(type, name) return cr_make_param_array(type, name, sizeof(name)/sizeof(type))

#define REDEF_LIGHT(function) \
	int  _ ## function ## _fail = 0; \
	void disable_ ## function() { function ## _fail = 1; } \
	void enable_ ## function() { function ## _fail = 0; } 

#define REDEF(function, fail_code, proto, ...) \
	REDEF_LIGHT(function) \
	int _tests_ ## function proto \
	{ \
		if (function ## _fail) \
			return fail_code; \
		return function(__VA_ARGS__); \
	}

#define REDEF_PROTO_LIGHT(function) \
	extern int function ## _fail; \
	void disable_ ## function(); \
	void enable_ ## function();

#define REDEF_PROTO(function, proto) \
	REDEF_PROTO_LIGHT(function); \
	int _tests_ ## function proto;

void _tests_mutex_init(void);
void _tests_mutex_close(void);
	
REDEF_PROTO(snprintf, (char *str, size_t size, const char *format, ...));
REDEF_PROTO(vsnprintf, (char *str, size_t size, const char *format, va_list arg));
REDEF_PROTO(fprintf, (FILE *stream, const char *format, ...));
REDEF_PROTO(strlen, (const char *s));

REDEF_PROTO_LIGHT(malloc);
void *_tests_malloc(size_t size);

#ifdef __linux__
REDEF_PROTO(sem_wait, (sem_t *sem));
REDEF_PROTO(sem_init, (sem_t *sem, int pshared, unsigned int value));
#elif _WIN32
#endif

#endif
