#include "test_writer.h"

static void tests_writer_setup(void)
{
	cr_redirect_stderr();
}

static void tests_writer_clean(void)
{

}

TestSuite(writer, .init=tests_writer_setup, .fini=tests_writer_clean);
