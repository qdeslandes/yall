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

        if (d->lines == NULL) {
                d->lines = l;
        } else {
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

void init_call_data(struct yall_call_data *d)
{
    d->message_size = 1;

    d->header = malloc(DEFAULT_LINE_SIZE);
    d->header[0] = '\n';
    d->header[1] = 0;
}

void convert_data_to_message(char *buffer, size_t len, struct yall_call_data *d)
{
        snprintf(buffer, len, "%s", d->header);
        free(d->header);

        struct yall_call_data_line *l = NULL;
        while ((l = remove_first_line(d))) {
                size_t curr_len = strlen(buffer);
                snprintf(&buffer[curr_len], len - curr_len, l->content);

                free(l->content);
                free(l);
        }
}

void yall_call_set_header(yall_call_data *d, const char *format, ...)
{
        if (d->header)
                d->message_size -= strlen(d->header);

        // Create the proper format with \n
        char *_format = malloc(strlen(format) + 2);
        snprintf(_format, strlen(format) + 2, "%s%c", format, '\n');

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

        uint8_t i = 0;
        for ( ; i < indent; ++i)
                line_content[i] = '\t';

        // Create the message line
        va_list args;
        va_start(args, format);

        vsnprintf(&line_content[i], DEFAULT_LINE_SIZE - indent, format, args);

        va_end(args);

        // Manage \n
        size_t len = strlen(line_content);
        line_content[len-1] = '\n';
        line_content[len] = '\0';

        // Add the line to the data list
        add_line(d, line_content);
        d->message_size += strlen(line_content);
}
