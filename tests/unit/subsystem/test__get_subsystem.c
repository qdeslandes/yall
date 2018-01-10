#include "test_subsystem.h"

/*
 * TODO : Check the returned file name in case of file output type.
 */

extern struct yall_subsystem *subsystems;
extern struct yall_subsystem *_subsystems[10];

extern struct yall_subsystem *_get_subsystem(const char *name,
        struct yall_subsystem *s,
        struct yall_subsystem_params *params);

// Test with empty subsystems list
Test(subsystem, test__get_subsystem0)
{
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
        // Without parameters
        cr_assert_eq(_get_subsystem("", subsystems, NULL), NULL);
        cr_assert_eq(_get_subsystem("204", subsystems, NULL), NULL);
        cr_assert_eq(_get_subsystem("0", subsystems, NULL), _subsystems[0]);
        cr_assert_eq(_get_subsystem("01", subsystems, NULL), _subsystems[5]);
        cr_assert_eq(_get_subsystem("200", subsystems, NULL), _subsystems[8]);

        // With parameters, using subsystems 0, 01 and 201
        struct yall_subsystem_params p = { 0 };
        cr_assert_eq(_get_subsystem("0", subsystems, &p), _subsystems[0]);
        cr_assert_eq(p.log_level, yall_debug);
        cr_assert_eq(p.output_type, yall_console_output);

        cr_assert_eq(_get_subsystem("01", subsystems, &p), _subsystems[5]);
        cr_assert_eq(p.log_level, yall_debug);
        cr_assert_eq(p.output_type, yall_console_output);

        cr_assert_eq(_get_subsystem("201", subsystems, &p), _subsystems[9]);
        cr_assert_eq(p.log_level, yall_debug);
        cr_assert_eq(p.output_type, yall_console_output);
}

/*
 * Test if the parameters are shallowed :
 * 	- subsystem 4
 * 	  |- subsystem 40
 * 	  |  |- subsystem 400
 * 	  |- subsystem 41
 * 	     |- subsystem 410
 * This way, if subsystem 41 inherit from subsystem 4 but subsystem 40 does not,
 * the parameters should not be shallowed.
 */
Test(subsystem, test__get_subsystem2, .init=create_subsystems, .fini=clean_subsystems)
{
	struct yall_subsystem_params p = { 0 };
	cr_assert_eq(_get_subsystem("41", subsystems, &p), _subsystems[13]);

	/*
	 * Here, p.log_level should have the value of subsystem 4
	 * (_subsystems[10]), but it has the value of subsystem 40
	 * (_subsystems[11]).
	 */
	cr_assert_eq(p.log_level, _subsystems[10]->log_level);
}