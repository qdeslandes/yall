#include "yall/call.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/*
 * add_line : add the given <content> to a new line of the data <d>.
 *      <d> and <content> can't be NULL.
 */
static void add_line(struct yall_call_data *d, char *content)
{
        struct yall_call_data_line *l = malloc(sizeof(struct yall_call_data_line));

        if (d->lines == NULL)
                d->lines = l;
        else {
                struct yall_call_data_line *tmp = d->lines;
                for ( ; tmp->next; tmp = tmp->next) ;
                tmp->next = l;
        }

        l->content = content;
        l->next = NULL;
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
