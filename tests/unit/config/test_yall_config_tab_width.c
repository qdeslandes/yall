#include "test_config.h"

extern struct yall_config current_config;
extern struct yall_config default_config;

Test(config, test_yall_config_set_tab_width0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    yall_config_set_tab_width(0);
    cr_assert_eq(current_config.tab_width, 0);

    yall_config_set_tab_width(5);
    cr_assert_eq(current_config.tab_width, 5);
}

Test(config, test_yall_config_get_tab_width0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    cr_assert_eq(yall_config_get_tab_width(), current_config.tab_width);

    yall_config_set_tab_width(8);
    cr_assert_eq(yall_config_get_tab_width(), 8);

    yall_config_set_tab_width(1);
    cr_assert_eq(yall_config_get_tab_width(), 1);
}

Test(config, test_yall_config_reset_tab_width0, .init=test_config_config_setup, .fini=test_config_config_clean)
{
    cr_assert_eq(yall_config_get_tab_width(), default_config.tab_width);
    yall_config_reset_tab_width();
    cr_assert_eq(yall_config_get_tab_width(), default_config.tab_width);

    yall_config_set_tab_width(6);
    yall_config_reset_tab_width();
    cr_assert_eq(current_config.tab_width, default_config.tab_width);
}
