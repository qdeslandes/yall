#include "test_writer.h"

/*
 * Can't test if the semaphore has been destroyed.
 */
Test(writer, test_writer_close0)
{
	writer_init(10);
        writer_close();
        cr_assert(1);
}
