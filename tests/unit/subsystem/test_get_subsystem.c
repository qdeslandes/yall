#include "test_subsystem.h"

// Empty subsystems list
Test(subsystem, test_get_subsystem0)
{
	// Without parameters
	cr_assert_eq(get_subsystem("NONE", NULL), NULL);

	// With parameters
	struct yall_subsystem_params p = { 0 };
	cr_assert_eq(get_subsystem("NONE", &p), NULL);
	cr_assert_eq(p.log_level, yall_warning);
	cr_assert_eq(p.output_type, yall_file_output);
	cr_assert_eq(p.status, yall_subsys_enable);
	cr_assert_eq(strcmp(p.output_file, "app.log"), 0);
}

// Filled subsystems list
Test(subsystem, test_get_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	// Without parameters
	cr_assert_eq(get_subsystem("0", NULL), _subsystems[0]);
	cr_assert_eq(get_subsystem("01", NULL), _subsystems[5]);
	cr_assert_eq(get_subsystem("201", NULL), _subsystems[9]);

	// With parameters
	struct yall_subsystem_params p = { 0 };

	cr_assert_eq(get_subsystem("1", &p), _subsystems[1]);
	cr_assert_eq(p.log_level, yall_notice);
	cr_assert_eq(p.status, yall_subsys_enable);
	cr_assert_eq(p.output_type, yall_console_output);

	cr_assert_eq(get_subsystem("02", &p), _subsystems[6]);
	cr_assert_eq(p.log_level, yall_warning);
	cr_assert_eq(p.status, yall_subsys_enable);
	cr_assert_eq(p.output_type, yall_console_output);

	cr_assert_eq(get_subsystem("200", &p), _subsystems[8]);
	cr_assert_eq(p.log_level, yall_warning);
	cr_assert_eq(p.status, yall_subsys_enable);
	cr_assert_eq(p.output_type, yall_console_output);
}
