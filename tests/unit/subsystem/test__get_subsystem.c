#include <criterion/criterion.h>
#include "yall/subsystem.h"
#include "h_subsystem.h"

extern struct yall_subsystem *_get_subsystem(const char *name,
	struct yall_subsystem *s,
	struct yall_subsystem_params *params);

// Test with empty subsystems list
Test(subsystem, test__get_subsystem0)
{
	extern struct yall_subsystem *subsystems;

	// Without parameters
	cr_assert_eq(_get_subsystem("", subsystems, NULL), NULL);
	cr_assert_eq(_get_subsystem("test", subsystems, NULL), NULL);

	// With parameters
	struct yall_subsystem_params p = { 0 };
	cr_assert_eq(_get_subsystem("", subsystems, &p), NULL);
	cr_assert_eq(_get_subsystem("test", subsystems, &p), NULL);
}

// Test with filled subsystems list
Test(subsystem, test__get_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	cr_assert(1);
}
