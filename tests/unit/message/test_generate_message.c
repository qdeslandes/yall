#include <stdarg.h>
#include <criterion/criterion.h>
#include "yall/message.h"
#include "yall/errors.h"
#include "h_subsystem.h"

Test(subsystem, test_generate_message0)
{
#ifdef __linux__
#warning This can't be tested currently, since generate_message require a va_list argument
#endif
    cr_assert(1);
}
