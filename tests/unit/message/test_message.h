#ifndef _TESTS_MESSAGE_H
#define _TESTS_MESSAGE_H

#include <stdarg.h>
#include <criterion/criterion.h>
#include <criterion/parameterized.h>

#include "h_utils.h"
#include "yall/message.h"
#include "yall/error.h"
#include "yall/log_level.h"

size_t std_wrapper(char *log_buffer, size_t len, const char *message_format, ...);

#endif
