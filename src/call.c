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
        uint16_t msg_curr_len = 0;

        if (d->header) {
                msg_curr_len = snprintf(buffer, len, "%s", d->header);
                free(d->header);
        } else {
                msg_curr_len = snprintf(buffer, len, "%s", "\n");
        }
        printf("==\n");
        printf("%d %d\n", buffer[0], buffer[1]);
        printf("==\n");

        struct yall_call_data_line *l = NULL;
        while ((l = remove_first_line(d))) {
                msg_curr_len += snprintf(&buffer[msg_curr_len], len - msg_curr_len, l->content);

                free(l->content);
                free(l);
        }
}

void yall_call_set_header(yall_call_data *d, const char *format, ...)
{
        if (d->header)
                d->message_size -= strlen(d->header);
        else
                d->header = malloc(DEFAULT_LINE_SIZE);

        // Create the proper format with \n
        char *_format = malloc(strlen(format) + 2);
        sprintf(_format, "%s%c", format, '\n');

        va_list args;
        va_start(args, format);

        vsnprintf(d->header, DEFAULT_LINE_SIZE, _format, args);
        d->message_size += strlen(d->header);

        va_end(args);

        free(_format);
}

void yall_call_add_line(yall_call_data *d, uint8_t indent, const char *format, ...)
{
        ++indent; // To, defaultly, set all line at 1 tab

        char *line_content = malloc(DEFAULT_LINE_SIZE);

        // Create the proper format with \t and \n
        uint8_t i = 0;
        char *_format = malloc(strlen(format) + indent + 2);
        for ( ; i < indent; ++i)
                _format[i] = '\t';
        sprintf(&_format[i], "%s%c", format, '\n');

        // Create the message line
        va_list args;
        va_start(args, format);

        vsnprintf(line_content, DEFAULT_LINE_SIZE, _format, args);

        va_end(args);

        // Add the line to the data list
        add_line(d, line_content);
        d->message_size += strlen(line_content);

        free(_format);
}
