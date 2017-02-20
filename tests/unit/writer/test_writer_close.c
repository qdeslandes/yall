#include <criterion/criterion.h>
#include "yall/writer.h"
#include "yall/errors.h"
#include "h_stream.h"

Test(subsystem, test_writer_close, .init=mutex_init)
{
	writer_close();
	cr_assert(1);
}
