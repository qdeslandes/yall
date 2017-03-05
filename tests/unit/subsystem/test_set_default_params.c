#include "test_subsystem.h"

Test(subsystem, test_set_default_params)
{
	struct yall_subsystem_params p = { 0 };

	set_default_params(&p);
	cr_assert_eq(p.log_level, yall_warning);
	cr_assert_eq(p.output_type, yall_file_output);
	cr_assert_eq(strcmp(p.output_file, "app.log"), 0);
}
