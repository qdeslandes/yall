#ifndef _TESTS_HELPERS_SUBSYSTEMS_H
#define _TESTS_HELPERS_SUBSYSTEMS_H

#include "yall/subsystem.h"

#define _NB_TEST_SUBSYSTEMS 16

/*
 * As this structure is defined inside a .c file, we need to redefine it here
 * to allow testing its content.
 */
struct yall_subsystem {
	char name[SUBSYS_NAME_LEN];
	enum yall_log_level log_level;
#ifdef __linux__
	_Atomic enum yall_subsys_status status;
#elif _WIN32
	enum yall_subsys_status status;
#endif
	enum yall_output_type output_type;
	char *output_file;
	bool delete_old_log_file;
	struct yall_subsystem *parent;
	struct yall_subsystem *childs;
	struct yall_subsystem *previous;
	struct yall_subsystem *next;
};

extern struct yall_subsystem *_subsystems[_NB_TEST_SUBSYSTEMS];

struct yall_subsystem *get_fake_subsystem(const char *name, const char *output_file);
void free_fake_subsystem(struct yall_subsystem *s);
void create_subsystems(void);
void clean_subsystems(void);

#endif
