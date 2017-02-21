#include <criterion/criterion.h>
#include "yall/utils.h"
#include "yall/errors.h"

Test(utils, test__yall_funcname0)
{
	cr_assert_eq(strcmp(_yall_funcname("Namespace::Class::Method()"), "Class::Method()"), 0);
	cr_assert_eq(strcmp(_yall_funcname("int main(void)"), "main(void)"), 0);
	cr_assert_eq(strcmp(_yall_funcname("Class::Method"), "Class::Method"), 0);
	cr_assert_eq(strcmp(_yall_funcname("main"), "main"), 0);
	cr_assert_eq(strcmp(_yall_funcname("0::0::0::main"), "0::main"), 0);
}
