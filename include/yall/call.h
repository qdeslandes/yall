#ifndef _YALL_CALL_H
#define _YALL_CALL_H

#include <stdint.h>

#include "yall/utils.h"

struct yall_call_data_line {
	char *content;
	struct yall_call_data_line *next;
};

typedef struct yall_call_data {
	uint16_t message_size;
	char *header;
	struct yall_call_data_line *lines;
} yall_call_data;

/*
 * call_custom_formatter : main function of this module. Its purprose is to
 *	call the provided format with the proper argument to generate a custom
 *	message. <formatter> can't be NULL. Once the formatter finished, a
 *	single message is generated and contains a printable string. This
 *	message is returned. It must be freed.
 */
const char *call_custom_formatter(
	void (*formatter)(yall_call_data *d, void *args),
	void *args);

#endif
