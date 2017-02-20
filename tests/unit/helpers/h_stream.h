#ifndef _TESTS_HELPERS_STREAM_H
#define _TESTS_HELPERS_STREAM_H

#include <stdint.h>

void redirect_streams(void);
void restore_streams(void);
uint8_t check_stderr(const char *content, int size);

void mutex_init(void);
void mutex_close(void);

#endif
