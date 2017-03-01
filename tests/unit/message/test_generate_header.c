#include "test_message.h"

struct param_test_generate_header message_params[9] = {
    { "", yall_debug, "", "                 ::: DEBUG     ::              :: " },
    { "", yall_warning, "", "                 ::: WARNING   ::              :: " },
    { "", yall_emerg, "", "                 ::: EMERGENCY ::              :: " },
    { "test", yall_debug, "", "test             ::: DEBUG     ::              :: " },
    { "test", yall_emerg, "", "test             ::: EMERGENCY ::              :: " },
    { "", yall_debug, "test", "                 ::: DEBUG     :: test         :: " },
    { "", yall_emerg, "test", "                 ::: EMERGENCY :: test         :: " },
    { "test", yall_debug, "test", "test             ::: DEBUG     :: test         :: " },
    { "test", yall_emerg, "test", "test             ::: EMERGENCY :: test         :: " }
};

/*
 * Valid snprintf
 */
ParameterizedTestParameters(message, test_generate_header0) {
	RETURN_PARAM(struct param_test_generate_header, message_params);
}

ParameterizedTest(struct param_test_generate_header *p, message, test_generate_header0)
{
    char buffer[128] = { 0 };

    cr_assert_eq(generate_header(buffer, p->s, p->ll, p->f), YALL_OK);
    cr_assert_eq(strncmp(buffer, p->waited, 50), 0);
}

/*
 * Invalid snprintf
 */
Test(message, test_generate_header1)
{
    char buffer[32] = { 0 };

    disable_snprintf();
    cr_assert_eq(generate_header(buffer, "test", yall_debug, "test"), YALL_STRING_WRITE_ERR);
    enable_snprintf();
}

/*
 * Writing a too long string
 */
Test(message, test_generate_header2)
{
    char buffer[YALL_MSG_LEN] = { 0 };
    char too_long_str[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    cr_assert_eq(generate_header(buffer, "test", yall_debug, too_long_str), YALL_OK);
}
