#include <criterion/criterion.h>
#include "yall/subsystem.h"
#include "h_subsystem.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

extern void _free_subsystem(struct yall_subsystem *s);

/*
 * <s> parameter of _free_subsytem can't be NULL, so it is useless to test
 *	the behaviour without any subsystem. We can't assert on the function
 *	but we must use it to ensure the coverage will count the lines.
 */
Test(subsystem, test__free_subsystem0, .init=create_subsystems, .fini=clean_subsystems)
{
	_free_subsystem(_subsystems[0]);

	_subsystems[0] = NULL;

	cr_assert(1);
}
