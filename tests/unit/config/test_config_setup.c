#include "test_config.h"

extern struct yall_config default_config;
extern struct yall_config current_config;

Test(config, test_config_setup0, .fini=test_config_setup_clean)
{
    config_setup();
    cr_assert_str_eq(current_config.std_header_template, default_config.std_header_template);
    cr_assert_str_eq(current_config.call_header_template, current_config.call_header_template);
    cr_assert_eq(current_config.tab_width, default_config.tab_width);
}
