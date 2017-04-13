#include "test_yall.h"

Test(yall, test_yall_get_version_string0)
{
        yall_get_version_string();
        cr_assert(1);
}
