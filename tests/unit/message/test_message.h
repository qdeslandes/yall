#ifndef _H_TESTS_MESSAGE
#define _H_TESTS_MESSAGE

#include <stdarg.h>
#include <criterion/criterion.h>
#include <criterion/parameterized.h>

#include "h_utils.h"
#include "yall/message.h"
#include "yall/errors.h"
#include "yall/log_levels.h"

struct test_trim {
	uint8_t length;
	const char function[64];
	char waited_function_name[64];
};

struct param_test_generate_header {
    const char s[32];
    enum yall_log_level ll;
    const char f[32];
    const char waited[96];
};

uint8_t trim_function_name(char *function_name, const char *function);

uint8_t generate_header(char *buffer,
    const char *subsystem,
    enum yall_log_level log_level,
    const char *function);

uint8_t wrapper(char *buffer,
    const char *format,
    const char *subsystem,
    enum yall_log_level log_level,
    const char *function,
    ...);

#endif
