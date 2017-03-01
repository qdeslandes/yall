#ifndef _H_TESTS_YALL
#define _H_TESTS_YALL

#include <stdbool.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/theories.h>

#include "h_subsystem.h"
#include "h_utils.h"

#include "yall/yall.h"
#include "yall/errors.h"
#include "yall/subsystem.h"

struct yall_subsystem *_get_subsystem(const char *name,
	struct yall_subsystem *s,
	struct yall_subsystem_params *params);

void tests_yall_log_setup(void);
void tests_yall_log_clean(void);
void tests_call_log_function(char *buffer, void *args);

#endif
