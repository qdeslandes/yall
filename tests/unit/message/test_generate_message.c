#include <stdarg.h>
#include <criterion/criterion.h>
#include <criterion/parameterized.h>

#include "h_utils.h"
#include "yall/message.h"
#include "yall/errors.h"

/*
 * We can't create a va_list from scratch. So, to test generate_message(),
 * we create a wrapper variadic function which create a va_list from its
 * arguments.
 */
uint8_t wrapper(char *buffer,
    const char *format,
    const char *subsystem,
    enum yall_log_level log_level,
    const char *function,
    ...)
{
    va_list args;
    va_start(args, function);

    return generate_message(buffer, format, subsystem, log_level, function, args);
}

/*
 * generate_header() failure
 */
Test(message, test_generate_message0)
{
    char buffer[32] = { 0 };

    DISABLE_SNPRINTF();
    cr_assert_eq(wrapper(buffer, "", "test", yall_debug, "test"), YALL_STRING_WRITE_ERR);
    ENABLE_SNPRINTF();
}

/*
 * vsnprintf() failure
 */
Test(message, test_generate_message1)
{
    char buffer[32] = { 0 };

    DISABLE_VSNPRINTF();
    cr_assert_eq(wrapper(buffer, "", "test", yall_debug, "test"), YALL_STRING_WRITE_ERR);
    ENABLE_VSNPRINTF();
}

/*
 * Message too long
 */
Test(message, test_generate_message2)
{
    char buffer[512] = { 0 };
    char too_long_string[512] = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    cr_assert_eq(wrapper(buffer, too_long_string, "test", yall_debug, "test"), YALL_STRING_WRITE_ERR);
}
