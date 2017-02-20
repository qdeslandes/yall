#include "h_stream.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __linux__
#include <unistd.h>
#endif

static int stderr_bak = 0;
static char buffer[1024] = { 0 };

void redirect_streams(void)
{
#ifdef __linux__
	fflush(stderr);
	stderr_bak = dup(STDERR_FILENO);
#endif

    freopen("NULL", "a", stderr);

#ifdef __linux__
	setvbuf(stderr, buffer, _IOFBF, 1024);
#endif;
}

void restore_streams(void)
{
    freopen("NULL", "a", stderr);

#ifdef __linux__
	dup2(stderr_bak, STDERR_FILENO);
#endif
}

uint8_t check_stderr(const char *content, int size)
{
    uint8_t ret = strncmp(buffer, content, size);

    for (int i = 0; i < 1024; ++i)
        buffer[i] = 0;

    fflush(stderr);

    return ret;
}
