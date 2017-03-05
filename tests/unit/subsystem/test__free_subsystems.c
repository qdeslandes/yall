#include "test_subsystem.h"

Test(subsystem, test__free_subsystems0)
{
	_free_subsystems(NULL);

	cr_assert(1);
}

Test(subsystem, test__free_subsystems1, .init=create_subsystems, .fini=clean_subsystems)
{
	_free_subsystems(subsystems->childs);
	_free_subsystems(subsystems->next->next->childs->childs);
	_free_subsystems(subsystems);

	for (int i = 0; i < 10; ++i)
		_subsystems[i] = NULL;

	cr_assert(1);
}
