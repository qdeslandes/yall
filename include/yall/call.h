#ifndef _YALL_CALL_H
#define _YALL_CALL_H

#include <stdint.h>
#include <stddef.h>

#include "yall/utils.h"

#define DEFAULT_LINE_SIZE       1024

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
 * init_call_data : from a yall_call_data pointer, message_size is set to 1
 *  and header contains "\n". The <d> pointer can't be NULL.
 */
void init_call_data(struct yall_call_data *d);

/*
 * call_data_to_buffer : fill the <buffer> of size <len> with the data of <d>.
 *      None of theses pointers can be NULL.
 */
void convert_data_to_message(char *buffer, size_t len, struct yall_call_data *d);

/*
 * yall_call_set_header : called by the user's formatter function, it allow to
 *      define the header of the log message. This header will be added just
 *      after the standard info header (with subsystem name, date, ...).
 *      Both <d> and <format> parameters can't be NULL.
 */
_YALL_PUBLIC void yall_call_set_header(
        yall_call_data *d,
        const char *format,
        ...);

/*
 * yall_call_add_line : called by the user's formatter function, it allow to
 *      add a line to the custom message. <indent> is the number of time plus
 *      one that '\t' will be added before the message. <d> and <format> can't
 *      be NULL.
 */
_YALL_PUBLIC void yall_call_add_line(
        yall_call_data *d,
        uint8_t indent,
        const char *format, ...);

#endif
