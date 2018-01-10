#include "test_subsystem.h"
#include "helpers/h_subsystem.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *get_next_subsystem(struct yall_subsystem *s,
	bool crawl_childs, int8_t *d);

/*
 * NULL parameters
 */
Test(subsystem, test_get_next_subsystem0, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	cr_assert_eq(get_next_subsystem(NULL, false, &d), NULL);
	cr_assert_eq(d, 0);
}

/*
 * Subsystem with <childs>, crawling them
 */
Test(subsystem, test_get_next_subsystem1, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	// Crawling childs
	cr_assert_eq(get_next_subsystem(subsystems, true, &d), subsystems->childs);
	cr_assert_eq(d, 1);
}

/*
 * Subsystem with <childs>, not crawling them, <next> available
 */
Test(subsystem, test_get_next_subsystem2, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	// Crawling childs
	cr_assert_eq(get_next_subsystem(_subsystems[2], false, &d), _subsystems[3]);
	cr_assert_eq(d, 0);
}

/*
 * Subsystem without <next> neither <parent> or <childs>
 */
Test(subsystem, test_get_next_subsystem3, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	// Crawling childs
	cr_assert_eq(get_next_subsystem(_subsystems[15], false, &d), NULL);

	/*
	 * Here, the is not reason to test <d> as the function returned NULL.
	 */
}

/*
 * Subsystem with a parent (who has a <next>), without <next> or <childs>
 */
Test(subsystem, test_get_next_subsystem4, .init=create_subsystems, .fini=clean_subsystems)
{
	int8_t d = 0;

	// Crawling childs
	cr_assert_eq(get_next_subsystem(_subsystems[6], false, &d), _subsystems[1]);
	cr_assert_eq(d, -1);
}
