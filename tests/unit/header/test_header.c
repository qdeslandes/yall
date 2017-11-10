#include "test_header.h"

static void tests_header_setup(void)
{
}

static void tests_header_clean(void)
{

}

TestSuite(header, .init=tests_header_setup, .fini=tests_header_clean);

void test_generate_hdr_setup(void)
{
	config_setup();
}

void test_generate_hdr_clean(void)
{
	config_clean();
}