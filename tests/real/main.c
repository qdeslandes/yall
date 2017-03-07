#include <stdio.h>

#include <yall/yall.h>

int main(void)
{
	yall_init();

	printf("%s, %d\n", yall_get_version_string(), yall_get_version());
	yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("longsubsystem", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("azertyazertyazerty", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("status", NULL, yall_debug, yall_console_output, NULL);

	YALL_DEBUG("test", "This is a test log message");
	YALL_WARNING("longsubsystem", "This is a test log message");
	YALL_ERR("test", "This is a test log message");
	YALL_ERR("azertyazertyazert", "test");

	/*
	 * Subsystem status
	 */
	YALL_WARNING("absent", "This subsystem does not exists");
	YALL_WARNING("status", "Activated");
	yall_disable_subsystem("status");
	YALL_ERR("status", "This should not appear");
	yall_enable_subsystem("status");
	YALL_ERR("status", "This should appear");

#ifdef _WIN32
	getchar();
#endif

	return 0;
}
