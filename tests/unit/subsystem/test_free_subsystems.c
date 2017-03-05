#include "test_subsystem.h"

Test(subsystem, test_free_subsystems0)
{
	free_subsystems();

	cr_assert(1);
}

Test(subsystem, test_free_subsystems1, .init=create_subsystems, .fini=clean_subsystems)
{
	free_subsystems();

	for (int i = 0; i < 10; ++i)
		_subsystems[i] = NULL;

	cr_assert(1);
}
