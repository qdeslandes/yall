#include "h_stream.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static int stderr_bak = 0;
static char buffer[1024] = { 0 };

void redirect_streams(void)
{
    fflush(stderr);
    stderr_bak = dup(STDERR_FILENO);

    freopen("NULL", "a", stderr);
    setvbuf(stderr, buffer, _IOFBF, 1024);
}

void restore_streams(void)
{
    freopen("NULL", "a", stderr);
    dup2(stderr_bak, STDERR_FILENO);
}

uint8_t check_stderr(const char *content, int size)
{
    int ret = strncmp(buffer, content, size);

    for (int i = 0; i < 1024; ++i)
        buffer[i] = 0;

    fflush(stderr);

    return ret;
}
