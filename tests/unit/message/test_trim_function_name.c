#include <criterion/criterion.h>
#include <criterion/parameterized.h>

#include "yall/message.h"

extern uint8_t trim_function_name(char *function_name, const char *function);

struct test_trim {
	uint8_t length;
	const char function[64];
	char waited_function_name[64];
};

ParameterizedTestParameters(message, test_trime_function0) {
	static struct test_trim params[] = {
		{ 12, "main", "main" },
		{ 12, "main()", "main" },
		{ 12, "int main", "main" },
		{ 12, "int main()", "main" },
		{ 12, " main()", "main" },
		{ 12, "A", "A" },
		{ 22, "A::A", "A::A" },
		{ 22, "A::A::A", "A::A" },
		{ 22, "A::A::A()", "A::A" },
		{ 22, "int A::A", "A::A" },
		{ 22, "int A::A()", "A::A" },
		{ 22, "int A::A::A", "A::A" },
		{ 22, "int A::A::A()", "A::A"}
	};

	return cr_make_param_array(struct test_trim, params, sizeof(params)/sizeof(struct test_trim));
}

ParameterizedTest(struct test_trim *p, message, test_trime_function0)
{
	char function_name[64] = { 0 };
	cr_assert_eq(trim_function_name(function_name, p->function), p->length);
	cr_assert_str_eq(function_name, p->waited_function_name);
}