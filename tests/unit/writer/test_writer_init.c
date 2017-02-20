#include <criterion/criterion.h>
#include "yall/writer.h"
#include "yall/errors.h"
#include "h_stream.h"

Test(subsystem, test_writer_init)
{
	cr_assert_eq(writer_init(), YALL_OK);
}
