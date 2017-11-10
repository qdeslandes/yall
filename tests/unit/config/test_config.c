#include "test_config.h"

extern struct yall_config default_config;
extern struct yall_config current_config;

static void tests_config_setup(void)
{
}

static void tests_config_clean(void)
{

}

TestSuite(config, .init=tests_config_setup, .fini=tests_config_clean);

void test_config_config_setup(void)
{
    config_setup();
}

void test_config_config_clean(void)
{
    config_clean();
}

void test_config_setup_clean(void)
{
    config_clean();
}

void test_config_clean_setup(void)
{
    config_setup();
}