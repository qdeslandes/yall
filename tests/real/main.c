#include <stdio.h>

#include <yall/yall.h>

int main(void)
{
	yall_init();

	yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("longsubsystem", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("azertyazertyazerty", NULL, yall_debug, yall_console_output, NULL);

	YALL_DEBUG("test", "This is a test log message");
	YALL_WARNING("longsubsystem", "This is a test log message");
	YALL_ERR("test", "This is a test log message");
	YALL_ERR("azertyazertyazerty", "test");

#ifdef _WIN32
	getchar();
#endif

	return 0;
}
