#include <criterion/criterion.h>
#include "yall/subsystem.h"
#include "h_subsystem.h"

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

// Empty subsystems list
Test(subsystem, test_update_subsystem0)
{
    struct yall_subsystem *s = get_fake_subsystem("0", NULL);

    update_subsystem(s, yall_crit, yall_console_output, NULL);
    cr_assert_eq(s->log_level, yall_crit);
    cr_assert_eq(s->output_type, yall_console_output);
    cr_assert_eq(s->output_file, NULL);
    cr_assert_eq(s->parent, NULL);
    cr_assert_eq(s->childs, NULL);
    cr_assert_eq(s->previous, NULL);
    cr_assert_eq(s->next, NULL);

    free_fake_subsystem(s);

    s = get_fake_subsystem("1", NULL);

    update_subsystem(s, yall_emerg, yall_file_output, "1.log");
    cr_assert_eq(s->log_level, yall_emerg);
    cr_assert_eq(s->output_type, yall_file_output);
    cr_assert_eq(strcmp(s->output_file, "1.log"), 0);
    cr_assert_eq(s->parent, NULL);
    cr_assert_eq(s->childs, NULL);
    cr_assert_eq(s->previous, NULL);
    cr_assert_eq(s->next, NULL);

    free_fake_subsystem(s);
}
