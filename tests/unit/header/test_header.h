#ifndef _TESTS_HEADER_H
#define _TESTS_HEADER_H

#include <stdbool.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "h_utils.h"
#include "yall/header.h"
#include "yall/errors.h"

void test_generate_hdr_setup(void);
void test_generate_hdr_clean(void);

#endif