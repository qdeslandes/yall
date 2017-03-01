#include <criterion/criterion.h>
#include "yall/subsystem.h"
#include "h_subsystem.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

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
