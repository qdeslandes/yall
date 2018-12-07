#include "benchmark.h"

#include "yall/call.h"

void call_add_message(uint32_t loops, uint32_t nb_messages)
{
	double t_dt_s = 0;

	for (uint32_t i = 0; i < loops; ++i) {
		yall_call_data *d = call_new();

		clock_t begin = clock();

		for (uint32_t j = 0; j < nb_messages; ++j)
			yall_call_add_line(d, (uint8_t)(j % 3), "Line number %d", j);
	
		clock_t elapsed = clock() - begin;

		call_delete(d);

		t_dt_s += (double)elapsed / CLOCKS_PER_SEC;
	}

	uint32_t t_msg = nb_messages * loops;

	printf("call_add_message results:\n");
	printf("\tTotal time: %.3lfs\n", t_dt_s);
	printf("\tTime for %d messages (avg.): %.3lfs\n", nb_messages, t_dt_s / loops);
	printf("\tMessages per second (avg.): %.0lf\n", (double)t_msg / (double)t_dt_s);
}

BENCHMARK(call_add_message(20, 20000));

/*
 * Performances history, done on a release build, 20 loops and 20000 messages
 *
 * First version, using a custom singly-linked-list
 *	- Total time: 18.706s
 *	- Time for 20000 messages (avg.): 0.935s
 *	- Messages per second (avg.): 21384
 * Use llist instead of a singly-linked-list
 *	- Total time: 0.092s
 *	- Time for 20000 messages (avg.): 0.005s
 *	- Messages per second (avg.): 4335855
 */
