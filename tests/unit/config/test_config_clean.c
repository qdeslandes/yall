#include "test_config.h"

extern struct yall_config current_config;

Test(config, test_config_clean0, .init=test_config_clean_setup)
{
    config_clean();

    cr_assert_eq(current_config.std_header_template, NULL);
    cr_assert_eq(current_config.call_header_template, NULL);
    cr_assert_eq(current_config.tab_width, 0);
}
