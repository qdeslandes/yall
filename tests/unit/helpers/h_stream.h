#ifndef _TESTS_HELPERS_STREAM_H
#define _TESTS_HELPERS_STREAM_H

#include <stdint.h>

void redirect_streams(void);
void restore_streams(void);
uint16_t content_size(const char *filename);

#endif
