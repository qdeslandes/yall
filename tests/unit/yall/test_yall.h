#ifndef _TESTS_YALL_H
#define _TESTS_YALL_H

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
struct yall_subsystem_params default_params;

void tests_yall_init_lib(void);
void tests_yall_close_lib(void);
void tests_yall_log_setup(void);
void tests_yall_log_clean(void);
void tests_call_log_function(struct yall_call_data *d, void *args);

#endif
