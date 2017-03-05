#include "test_subsystem.h"

/*
 * Test parameters combination
 */
TheoryDataPoints(subsystem, test_create_subsystem0) = {
	DataPoints(char *, "short", "middlename", "toolongnameforasubsystemidkwhattodowiththat"),
	DataPoints(enum yall_log_level, yall_debug, yall_info, yall_notice, yall_warning, yall_err, yall_crit, yall_alert, yall_emerg),
	DataPoints(enum yall_output_type, yall_console_output, yall_file_output, yall_inherited_output),
	DataPoints(char *, "log.log")
};

Theory((char *n, enum yall_log_level ll, enum yall_output_type ot, char *of), subsystem, test_create_subsystem0)
{
	char subsys_name[SUBSYS_NAME_LEN] = { 0 };
	strncpy(subsys_name, n, SUBSYS_NAME_LEN - 1);

	struct yall_subsystem *s = create_subsystem(n, ll, ot, of);

	cr_assert(s);
	cr_assert_eq(s->parent, NULL);
	cr_assert_eq(s->childs, NULL);
	cr_assert_eq(s->previous, NULL);
	cr_assert_eq(s->next, NULL);
	cr_assert_str_eq(s->name, subsys_name);
	cr_assert_eq(s->log_level, ll);
	cr_assert_eq(s->output_type, ot);
	cr_assert_str_eq(s->output_file, of);
}

/*
 * 1st malloc failing
 */
Test(subsystem, test_create_subsystem1)
{
	disable_malloc();
	cr_assert(! create_subsystem("o", yall_debug, yall_console_output, NULL));
	enable_malloc();
}
