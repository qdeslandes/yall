#include <criterion/criterion.h>
#include "yall/message.h"
#include "yall/errors.h"
#include "h_subsystem.h"

uint8_t generate_header(char *buffer,
    const char *subsystem,
    enum yall_log_level log_level,
    const char *function);

// TODO : Test with a string too long (buffer overflow)
Test(subsystem, test_generate_header)
{
    char buffer[128] = { 0 };

    cr_assert_eq(generate_header(buffer, "0", yall_debug, "call"), YALL_OK);
    cr_assert_eq(strncmp(buffer, "0 ::: DEBUG     :: call :: ", 27), 0);

    cr_assert_eq(generate_header(buffer, "00", yall_crit, "called"), YALL_OK);
    cr_assert_eq(strncmp(buffer, "00 ::: CRITICAL  :: called :: ", 30), YALL_OK);
}
