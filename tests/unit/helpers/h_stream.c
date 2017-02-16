#include "h_stream.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static int stderr_bak = 0;

void redirect_streams(void)
{
    stderr_bak = dup(STDERR_FILENO);

    freopen("unit.log", "w", stderr);
}

void restore_streams(void)
{
    dup2(stderr_bak, STDERR_FILENO);
    close(stderr_bak);
}

uint8_t check_output(const char *filename, const char *content)
{
    FILE *f = fopen(filename, "r");
    int ret = 0;
    int length = 0;
    char *buffer = NULL;

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);

        if (buffer) {
            fread(buffer, 1, length, f);
            ret = strcmp(buffer, content);
            free(buffer);
        }

        fclose(f);
    }

    return ret;
}
