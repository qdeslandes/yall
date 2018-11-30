#include "benchmark.h"

void benchmark_add_call_data(uint32_t loops, uint32_t nb_messages)
{
	double t_dt_s = 0;

	for (uint32_t i = 0; i < loops; ++i) {
		yall_call_data d = { 0 };
		init_call_data(&d);

		clock_t begin = clock();

		for (uint32_t j = 0; j < nb_messages; ++j) {
			yall_call_add_line(&d, 1, "Testing %d", j);
		}

		clock_t elapsed = clock() - begin;
		t_dt_s += (double)elapsed / CLOCKS_PER_SEC;
	}

	uint32_t t_msg = nb_messages * loops;

	printf("Benchmark results:\n");
	printf("\tTotal time: %.3lfs\n", t_dt_s);
	printf("\tTime for %d messages (avg.): %.3lfs\n", nb_messages, t_dt_s / loops);
	printf("\tMessages per second (avg.): %.0lf\n", (double)t_msg / (double)t_dt_s);
}

BENCHMARK(benchmark_add_call_data(20, 10000));

/*
 * History of algorithm performances (10 loops, 100000 messages):
 * Original:
 * 	- Total time: 11.027s
 * 	- Time for 10000 messages (avg.): 0.551s
 * 	- Messages per second (avg.): 18137
 */