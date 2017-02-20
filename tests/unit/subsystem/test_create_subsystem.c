#include <criterion/criterion.h>
#include "yall/subsystem.h"
#include "h_subsystem.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

// Empty subsystems list
Test(subsystem, test_create_subsystem0)
{
	// Without console output
	struct yall_subsystem *s = NULL;
	s = create_subsystem("", yall_debug, yall_console_output, NULL);
	cr_assert(s);
	cr_assert_eq(s->parent, NULL);
	cr_assert_eq(s->childs, NULL);
	cr_assert_eq(s->previous, NULL);
	cr_assert_eq(s->next, NULL);
	cr_assert_eq(strcmp(s->name, ""), 0);
	cr_assert_eq(s->log_level, yall_debug);
	cr_assert_eq(s->output_type, yall_console_output);
	cr_assert_eq(s->output_file, NULL);

    free_fake_subsystem(s);

	// With file output
	s = create_subsystem("0", yall_debug, yall_console_output, "test");
	cr_assert(s);
	cr_assert_eq(strcmp(s->name, "0"), 0);
	cr_assert_eq(s->log_level, yall_debug);
	cr_assert_eq(s->output_type, yall_console_output);
	cr_assert_eq(strcmp(s->output_file, "test"), 0);

    free_fake_subsystem(s);
}
