#include "test_subsystem.h"

/*
 * No subsystem available
 */
Test(subsystem, test_set_subsys_status0)
{
        set_subsys_status("test", yall_subsys_disable);
        set_subsys_status("test", yall_subsys_enable);

        cr_assert(1);
}

/*
 * With test subsystems
 */
Test(subsystem, test_set_subsys_status1, .init=create_subsystems, .fini=clean_subsystems)
{
        set_subsys_status("0", yall_subsys_disable);
        cr_assert_eq(_subsystems[0]->status, yall_subsys_disable);

        set_subsys_status("01", yall_subsys_disable);
        cr_assert_eq(_subsystems[5]->status, yall_subsys_disable);
}
