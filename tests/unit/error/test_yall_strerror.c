#include "test_error.h"

extern struct yall_errordesc {
	yall_error code;
	const char *message;
} errordesc[];

/*
 * Value too low
 */
Test(error, test_yall_strerror0)
{
	cr_assert_str_eq(yall_strerror((yall_error)-1), errordesc[YALL_UNKNOW_ERROR].message);
}

/*
 * Value too high
 */
Test(error, test_yall_strerror1)
{
	cr_assert_str_eq(yall_strerror(yall_err_end), errordesc[YALL_UNKNOW_ERROR].message);
	
	cr_assert_str_eq(yall_strerror(yall_err_end+1), errordesc[YALL_UNKNOW_ERROR].message);
}

/*
 * Correct value
 */
Test(error, test_yall_strerror2)
{
	for (int i = 0; i < yall_err_end; ++i) {
		const char *str = errordesc[i].message;
		cr_assert_str_eq(yall_strerror(i), str);
	}
}