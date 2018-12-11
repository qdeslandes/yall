#ifndef _BENCHMARK_H
#define _BENCHMARK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#define BENCHMARK(function) \
int main(void) \
{ \
	function; \
}

#endif
