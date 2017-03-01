#include "test_message.h"

static void tests_message_setup(void)
{

}

static void tests_message_clean(void)
{

}

TestSuite(message, .init=tests_message_setup, .fini=tests_message_clean);

/*
 * We can't create a va_list from scratch. So, to test generate_message(),
 * we create a wrapper variadic function which create a va_list from its
 * arguments.
 */
uint8_t wrapper(char *buffer,
	const char *format,
	const char *subsystem,
	enum yall_log_level log_level,
	const char *function,
	...)
{
	va_list args;
	va_start(args, function);

	return generate_message(buffer, format, subsystem, log_level, function, args);
}

