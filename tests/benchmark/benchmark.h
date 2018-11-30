#ifndef _YALL_BENCHMARK_H
#define _YALL_BENCHMARK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "yall/yall.h"

#define BENCHMARK(function_call) \
int main(void) \
{ \
    function_call; \
    return 0; \
}

#endif
