#ifndef _H_TESTS_YALL
#define _H_TESTS_YALL

#include <stdbool.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/theories.h>

#include "h_subsystem.h"

#include "yall/yall.h"
#include "yall/errors.h"
#include "yall/subsystem.h"

void tests_yall_log_setup(void);
void tests_yall_log_clean(void);

#endif
