#ifndef _TESTS_CONFIG_H
#define _TESTS_CONFIG_H

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "helpers/h_utils.h"
#include "yall/config.h"
#include "yall/error.h"

void test_config_config_setup(void);
void test_config_config_clean(void);
void test_config_setup_clean(void);
void test_config_clean_setup(void);

#endif
