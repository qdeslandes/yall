#ifndef _TESTS_HELPERS_SUBSYSTEMS_H
#define _TESTS_HELPERS_SUBSYSTEMS_H

struct yall_subsystem *get_fake_subsystem(const char *name, const char *output_file);
void free_fake_subsystem(struct yall_subsystem *s);
void create_subsystems(void);
void clean_subsystems(void);

#endif
