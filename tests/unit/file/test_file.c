#include "test_file.h"

static void tests_file_setup(void)
{
}

static void tests_file_clean(void)
{

}

TestSuite(file, .init=tests_file_setup, .fini=tests_file_clean);
