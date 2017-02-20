#include <criterion/criterion.h>
#include "yall/subsystem.h"
#include "h_subsystem.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

extern void _free_subsystems(struct yall_subsystem *s);

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
