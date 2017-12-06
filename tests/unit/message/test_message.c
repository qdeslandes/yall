#include "test_message.h"

#include <stdarg.h>

static void tests_message_setup(void)
{
	yall_init();
}

static void tests_message_clean(void)
{
	yall_close_all();
}

TestSuite(message, .init=tests_message_setup, .fini=tests_message_clean);

/*
 * We can't create a va_list from scratch. So, to test generate_message(),
 * we create a wrapper variadic function which create a va_list from its
 * arguments.
 */
size_t std_wrapper(char *log_buffer, size_t len, const char *message_format, ...)
{
	size_t _len = 0;
        va_list args;
        va_start(args, message_format);

	//_len = generate_std_msg(log_buffer, len, message_format, args);
	
	va_end(args);

	return _len;
}

