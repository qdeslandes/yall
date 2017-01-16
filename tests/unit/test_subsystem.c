#include <criterion/criterion.h>
#include "yall/subsystem.h"

Test(subsystem, test_get_subsystem)
{
	cr_assert_null(get_subsystem("none", NULL));
}
