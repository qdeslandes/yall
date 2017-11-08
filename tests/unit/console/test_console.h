#ifndef _TESTS_CONSOLE_H
#define _TESTS_CONSOLE_H

#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/parameterized.h>

#include "h_utils.h"
#include "yall/yall.h"
#include "yall/error.h"
#include "yall/console.h"

struct param_set_color {
        enum yall_log_level ll;
        uint8_t code;
};

struct param_set_color ll_and_colors[8];

void reset_color(void);
void set_color(enum yall_log_level log_level);
void test_write_log_console_setup(void);
void test_write_log_console_clean(void);

#endif
