#include "test_subsystem.h"

/*
 * No subsystem available
 */
Test(subsystem, test_yall_enable_subsystem0)
{
	yall_enable_subsystem("test");
	yall_enable_subsystem("test");

	cr_assert(1);
}

/*
 * With test subsystems
 */
Test(subsystem, test_yall_enable_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	_subsystems[0]->status = yall_subsys_disable;
	_subsystems[5]->status = yall_subsys_disable;

	yall_enable_subsystem("0");
	cr_assert_eq(_subsystems[0]->status, yall_subsys_enable);

	yall_enable_subsystem("01");
	cr_assert_eq(_subsystems[5]->status, yall_subsys_enable);
}
