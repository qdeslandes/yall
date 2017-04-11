#include "yall/call.h"

#include <stdlib.h>

static void call_data_to_buffer(char *buffer, struct yall_call_data *d)
{

}

const char *call_custom_formatter(
	void (*formatter)(yall_call_data *d, void *args),
	void *args)
{
	struct yall_call_data d = { 0 };

	formatter(&d, args);

	char *buffer = malloc(d.message_size + 1);
	if (! buffer)
		goto end;

	call_data_to_buffer(buffer, &d);

end:
	return buffer;
}
