#include "h_stream.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static int stderr_bak = 0;

void redirect_streams(void)
{
    stderr_bak = dup(STDERR_FILENO);

    freopen("tmp.txt", "w", stderr);
}

void restore_streams(void)
{
    dup2(stderr_bak, STDERR_FILENO);
    close(stderr_bak);
}

uint16_t content_size(const char *filename)
{
    struct stat sb;

    stat(filename, &sb);

    return sb.st_size;
}
