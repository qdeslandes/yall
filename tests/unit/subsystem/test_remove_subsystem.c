#include <criterion/criterion.h>
#include "yall/subsystem.h"
#include "h_subsystem.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

// Empty subsystems list
Test(subsystem, test_remove_subsystem0)
{
	cr_assert_eq(remove_subsystem("0"), NULL);
	cr_assert_eq(remove_subsystem("nope"), NULL);
}

// Filled subsystems list
Test(subsystem, test_remove_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	struct yall_subsystem *s = NULL;

	// At the end
	cr_assert_eq((s = remove_subsystem("3")), _subsystems[3]);
	cr_assert_eq(_subsystems[2]->next, NULL);

	// In the middle without childs
	cr_assert_eq((s = remove_subsystem("1")), _subsystems[1]);
	cr_assert_eq(_subsystems[0]->next, _subsystems[2]);
	cr_assert_eq(_subsystems[2]->previous, _subsystems[0]);

	// With childs
	cr_assert_eq((s = remove_subsystem("2")), _subsystems[2]);
	cr_assert_eq(_subsystems[0]->next, NULL);
	cr_assert_eq(s->childs, _subsystems[7]);
}

// Remove the first one
Test(subsystem, test_remove_subsystem2, .init=create_subsystems, .fini=clean_subsystems)
{
	struct yall_subsystem *s = NULL;

	cr_assert_eq((s = remove_subsystem("0")), _subsystems[0]);
	cr_assert_eq(subsystems, _subsystems[1]);
}
