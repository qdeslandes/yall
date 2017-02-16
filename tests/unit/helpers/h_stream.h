#ifndef _TESTS_HELPERS_STREAM_H
#define _TESTS_HELPERS_STREAM_H

#include <stdint.h>

void redirect_streams(void);
void restore_streams(void);
uint8_t check_ouput(const char *filename, const char *content);

#endif
