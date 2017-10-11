#include "test_config.h"

extern struct yall_config current_config;
extern struct yall_config default_config;

Test(config, test_yall_config_set_call_header_template0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    yall_config_set_call_header_template("%l %0.4f");
    cr_assert_str_eq(current_config.call_header_template, "%l %0.4f");

    yall_config_set_call_header_template("%sl %0.4f");
    cr_assert_str_eq(current_config.call_header_template, "%sl %0.4f");
}

Test(config, test_yall_config_get_call_header_template0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    cr_assert_str_eq(yall_config_get_call_header_template(), default_config.call_header_template);

    yall_config_set_call_header_template("%l %0.4f");
    cr_assert_str_eq(yall_config_get_call_header_template(), "%l %0.4f");

    yall_config_set_call_header_template("%sl %0.4f");
    cr_assert_str_eq(yall_config_get_call_header_template(), "%sl %0.4f");
}

Test(config, test_yall_config_reset_call_header_template0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    cr_assert_str_eq(yall_config_get_call_header_template(), default_config.call_header_template);
    yall_config_reset_call_header_template();
    cr_assert_str_eq(yall_config_get_call_header_template(), default_config.call_header_template);

    yall_config_set_call_header_template("%l %0.4f");
    yall_config_reset_call_header_template();
    cr_assert_str_eq(current_config.call_header_template, default_config.call_header_template);
}
