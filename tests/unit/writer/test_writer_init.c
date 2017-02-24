#include <criterion/criterion.h>

#include "h_utils.h"
#include "yall/writer.h"
#include "yall/errors.h"

/*
 * Correct test
 */
Test(writer, test_writer_init0)
{
	cr_assert_eq(writer_init(), YALL_OK);
}

/*
 * sem_init() fail
 */
Test(writer, test_writer_init1)
{
    DISABLE_SEM_INIT();
    cr_assert_eq(writer_init(), YALL_SEM_INIT_ERR);
    ENABLE_SEM_INIT();
}
