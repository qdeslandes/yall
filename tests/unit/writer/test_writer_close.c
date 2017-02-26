#include <criterion/criterion.h>
#include <semaphore.h>

#include "yall/writer.h"
#include "yall/errors.h"

extern sem_t console_sem;
extern sem_t file_sem;

/*
 * Can't test if the semaphore has been destroyed.
 */
Test(writer, test_writer_close0)
{
	writer_close();
	cr_assert(1);
}
