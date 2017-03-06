#ifndef _TESTS_YALL_H
#define _TESTS_YALL_H

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/parameterized.h>
#include <criterion/theories.h>

#include "h_utils.h"
#include "h_subsystem.h"
#include "yall/yall.h"
#include "yall/subsystem.h"

struct yall_subsystem *subsystems;
struct yall_subsystem *_subsystems[10];

struct yall_subsystem *_get_subsystem(const char *name,
	struct yall_subsystem *s,
	struct yall_subsystem_params *params);
void _free_subsystem(struct yall_subsystem *s);
void _free_subsystems(struct yall_subsystem *s);
void set_default_params(struct yall_subsystem_params *params);
void set_subsys_status(const char *subsys_name, enum yall_subsys_status status);

#endif
