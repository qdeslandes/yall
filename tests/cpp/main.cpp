#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <yall/yall.h>

namespace test {
class Class {
	private:
		int a;

	public:
		Class() {
			YALL_ERR("class", "Constructor");
		}
};

namespace othertest {
class Test {
	private:
		int a;
	public:
		Test() {
			YALL_WARNING("class", "Constructor");
		}

		void makeitwayne() {
			YALL_NOTICE("class", "RAIN");
		}
};
}
};

int main(void)
{
	yall_init();

	yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("longsubsystem", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("azertyazertyazerty", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("class", NULL, yall_debug, yall_console_output, NULL);

	YALL_DEBUG("test", "This is a test log message");
	YALL_WARNING("longsubsystem", "This is a test log message");
	YALL_ERR("test", "This is a test log message");
	YALL_ERR("azertyazertyazerty", "test");

	test::Class c = test::Class();
	test::othertest::Test t = test::othertest::Test();
	t.makeitwayne();

	return 0;
}
