/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef YUNIT_TESTS_H
#define YUNIT_TESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <jansson.h>

#include "yall/yall.h"
#include "yall/message.h"
#include "yall/config/parameters.h"
#include "yall/container/cqueue.h"
#include "yall/error.h"
#include "yall/subsystem.h"
#include "yall/config/reader.h"
#include "yall/config/parameters.h"

#include <semaphore.h>
#define NULL_FILE "/dev/null"

#define _NB_TEST_SUBSYSTEMS 16
#define _YALL_TEST_JSON_FILE "./yall.json"

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
	void disable_ ## function(void); \
	void enable_ ## function(void)

#define TESTS_REDEFINE_PROTO(function, proto) \
	TESTS_REDEFINE_PROTO_LIGHT(function); \
	int _tests_ ## function proto

void _tests_hide_stderr(void);
void _tests_restore_stderr(void);
void _tests_mutex_init(void);
void _tests_mutex_close(void);

TESTS_REDEFINE_PROTO(snprintf, (char *str, size_t size, const char *format, ...));
TESTS_REDEFINE_PROTO(fprintf, (FILE *stream, const char *format, ...));
TESTS_REDEFINE_PROTO(vsnprintf, (char *str, size_t size, const char *format, va_list arg));
TESTS_REDEFINE_PROTO(strlen, (const char *s));
TESTS_REDEFINE_PROTO(pthread_create, (pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg));

TESTS_REDEFINE_PROTO_LIGHT(malloc);
void *_tests_malloc(size_t size);

TESTS_REDEFINE_PROTO_LIGHT(fopen);
FILE *_tests_fopen(const char *pathname, const char *mode);

TESTS_REDEFINE_PROTO(sem_wait, (sem_t *sem));
TESTS_REDEFINE_PROTO(sem_init, (sem_t *sem, int pshared, unsigned int value));

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[_NB_TEST_SUBSYSTEMS];

void test_init_yall(void);
void test_close_yall(void);
void test_create_json_config_file(void);
void test_remove_json_config_file(void);
void create_subsystems(void);
void clean_subsystems(void);

#endif
