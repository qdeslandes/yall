#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <yall/yall.h>

const char *tmp(const char *s)
{
	int len = strlen(s);
	int t = 0;

	for (; len > 0; --len) {
		if (s[len] == ':')
			++t;

		if (t == 3 || s[len] == ' ')
			return &s[len+1];
	}

	return s;
}

namespace test {
class Class {
	private:
		int a;

	public:
		Class() {
			YALL_ERR("class", "Constructor");
			YALL_ERR("class", tmp(__PRETTY_FUNCTION__));
			YALL_WARNING("class", tmp("main()"));
		}
};
};

int main(void)
{
	yall_init();

	yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("longsubsystem", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("azertyazertyazerty", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("class", NULL, yall_debug, yall_console_output, NULL);

	YALL_DEBUG("test", tmp(__PRETTY_FUNCTION__));
	YALL_DEBUG("test", "This is a test log message");
	YALL_WARNING("longsubsystem", "This is a test log message");
	YALL_ERR("test", "This is a test log message");
	YALL_ERR("azertyazertyazerty", "test");

	test::Class c = test::Class();

	return 0;
}
