#include "test_yall.h"

Test(yall, test_yall_get_version0)
{
        yall_get_version();
        cr_assert(1);
}
