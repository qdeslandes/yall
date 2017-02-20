#include <criterion/criterion.h>
#include "yall/writer.h"
#include "yall/errors.h"
#include "h_stream.h"

#include <semaphore.h>
extern sem_t console_sem;
extern sem_t file_sem;

Test(subsystem, test_writer_close, .init=mutex_init)
{
	writer_close();
	cr_assert(1);
}
