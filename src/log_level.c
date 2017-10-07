#include "yall/log_level.h"

static char *log_level_str[8] = {
		"DEBUG",
		"INFO",
		"NOTICE",
		"WARNING",
		"ERROR",
		"CRITICAL",
		"ALERT",
		"EMERGENCY"
	};

const char *get_log_level_name(enum yall_log_level log_level)
{
	return log_level_str[log_level];
}