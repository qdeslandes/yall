#include <criterion/criterion.h>
#include "yall/subsystem.h"
#include "h_subsystem.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

Test(subsystem, test_add_subsystem0)
{
	// Without parent
	struct yall_subsystem *s = get_fake_subsystem("0", NULL);
	add_subsystem(NULL, s);
	cr_assert_eq(subsystems, s);

	s = get_fake_subsystem("1", NULL);
	add_subsystem(NULL, s);
	cr_assert_eq(subsystems->next, s);
	cr_assert_eq(s->previous, subsystems);

	s = get_fake_subsystem("2", NULL);
	add_subsystem(NULL, s);
	cr_assert_eq(subsystems->next->next, s);
	cr_assert_eq(s->previous, subsystems->next);

	// With parent
	s = get_fake_subsystem("00", NULL);
	add_subsystem("0", s);
	cr_assert_eq(subsystems->childs, s);
	cr_assert_eq(s->parent, subsystems);

	s = get_fake_subsystem("20", NULL);
	add_subsystem("2", s);
	cr_assert_eq(subsystems->next->next->childs, s);
	cr_assert_eq(s->parent, subsystems->next->next);

	s = get_fake_subsystem("21", NULL);
	add_subsystem("2", s);
	cr_assert_eq(subsystems->next->next->childs->next, s);
	cr_assert_eq(s->parent, subsystems->next->next);
	cr_assert_eq(s->previous, subsystems->next->next->childs);

	// Without parent (last time)
	s = get_fake_subsystem("3", NULL);
	add_subsystem(NULL, s);
	cr_assert_eq(subsystems->next->next->next, s);
	cr_assert_eq(s->previous, subsystems->next->next);

	free_fake_subsystem(subsystems->next->next->next);
	free_fake_subsystem(subsystems->next->next->childs->next);
	free_fake_subsystem(subsystems->next->next->childs);
	free_fake_subsystem(subsystems->next->next);
	free_fake_subsystem(subsystems->next);
	free_fake_subsystem(subsystems->childs);
	free_fake_subsystem(subsystems);
	subsystems = NULL;
}
