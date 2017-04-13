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

/*
 * remove_first_line : remove and return the first line of the given data <d>.
 */
static struct yall_call_data_line *remove_first_line(struct yall_call_data *d)
{
        struct yall_call_data_line *l = d->lines;

        if (l) {
                d->lines = l->next;
                d->message_size -= strlen(l->content);
        }

        return l;
}

void convert_data_to_message(char *buffer, size_t len, struct yall_call_data *d)
{
        uint16_t msg_len = d->message_size;
        uint16_t msg_curr_len = 0;

        if (d->header) {
                msg_curr_len = snprintf(buffer, len, d->header);
                free(d->header);
        } else {
                msg_curr_len = snprintf(buffer, len, "\n");
        }

        struct yall_call_data_line *l = NULL;
        while ((l = remove_first_line(d))) {
                msg_curr_len += snprintf(&buffer[msg_curr_len], len - msg_curr_len, l->content);

                free(l->content);
                free(l);
        }
}

	char *buffer = malloc(d.message_size + 1);
	if (! buffer)
		goto end;

	call_data_to_buffer(buffer, &d);

end:
	return buffer;
}
