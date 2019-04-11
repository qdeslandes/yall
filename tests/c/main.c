/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include <yall/yall.h>

#define CONFIG_FILE "./yall.config"

static pthread_t threads[5];

void memoryInfos(struct yall_call_data *d, const void *args);

void *thread0(void *args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_c_test", "%s, %d", yall_get_version_string(), yall_get_version());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_INFO("yall_c_test", "Trying to reinit library : %s", yall_strerror(yall_init()));
		YALL_CALL_ERR("memory", memoryInfos, NULL);
	}

	return NULL;
}

void *thread1(void *args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_c_test", "%s, %d", yall_get_version_string(), yall_get_version());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_INFO("yall_c_test", "Trying to reinit library : %s", yall_strerror(yall_init()));
		YALL_CALL_ERR("memory", memoryInfos, NULL);
	}

	return NULL;
}

void *thread2(void *args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_c_test", "%s, %d", yall_get_version_string(), yall_get_version());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_INFO("yall_c_test", "Trying to reinit library : %s", yall_strerror(yall_init()));
		YALL_CALL_ERR("memory", memoryInfos, NULL);
	}

	return NULL;
}

void *thread3(void * args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_c_test", "%s, %d", yall_get_version_string(), yall_get_version());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_INFO("yall_c_test", "Trying to reinit library : %s", yall_strerror(yall_init()));
		YALL_CALL_ERR("memory", memoryInfos, NULL);
	}

	return NULL;
}

void *thread4(void *args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_c_test", "%s, %d", yall_get_version_string(), yall_get_version());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_INFO("yall_c_test", "Trying to reinit library : %s", yall_strerror(yall_init()));
		YALL_CALL_ERR("memory", memoryInfos, NULL);
	}

	return NULL;
}

void benchmark_output(uint32_t loops, uint32_t nb_messages)
{
	double t_dt_s = 0;

	for (uint32_t i = 0; i < loops; ++i) {
		clock_t begin = clock();

		yall_init();
		yall_set_subsystem("yall_c_test", NULL, yall_debug, yall_console_output, NULL);

		for (uint32_t j = 0; j < nb_messages; ++j) {
			YALL_DEBUG("yall_c_test", "message %d", j);
		}

		yall_close_all();

		clock_t elapsed = clock() - begin;
		t_dt_s += (double)elapsed / CLOCKS_PER_SEC;
	}

	uint32_t t_msg = nb_messages * loops;

	printf("Benchmark results:\n");
	printf("\tTotal time: %.3lfs\n", t_dt_s);
	printf("\tTime for %d messages (avg.): %.3lfs\n", nb_messages, t_dt_s / loops);
	printf("\tMessages per second (avg.): %.0lf\n", (double)t_msg / (double)t_dt_s);
}

int main(int argc, char *argv[])
{
	const char *config_file = NULL;

	config_file = argc == 1 ? CONFIG_FILE : argv[1];

	yall_init();
	yall_init();

	yall_config_set_tab_width(4);
	yall_config_set_std_header_template("[%d] :: line %-4.4L :: %-9l : %f : \n\t");
	yall_config_set_call_header_template("[%d] :: %-9l : %s : ");

	yall_set_subsystem("yall_c_test", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("io", "yall_c_test", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("memory", "yall_c_test", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("manager", "memory", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("DDR3", "memory", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("DDR4", "memory", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("CPU", "yall_c_test", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("ALU", "CPU", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("Executor", "CPU", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("scheduler", "yall_c_tests", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("debug", "yall_c_tests", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("syslog_yall", NULL, yall_debug, yall_syslog_output, NULL);
	yall_enable_debug("debug");

	yall_load_configuration(config_file);

	yall_show_subsystems_tree();

	pthread_create(&threads[0], NULL, thread0, NULL);
	pthread_create(&threads[1], NULL, thread1, NULL);
	pthread_create(&threads[2], NULL, thread2, NULL);
	pthread_create(&threads[3], NULL, thread3, NULL);
	pthread_create(&threads[4], NULL, thread4, NULL);

	YALL_DEBUG("yall_c_test", "%s, %d", yall_get_version_string(), yall_get_version());
	YALL_DEBUG("io", "IO subsystem ready.");
	YALL_INFO("yall_c_test", "Trying to reinit library : %s", yall_strerror(yall_init()));
	YALL_CALL_ERR("memory", memoryInfos, NULL);

	YALL_ALERT("scheduler" , "Using process 7034.");

	yall_disable_subsystem("scheduler");
	YALL_DEBUG("scheduler", "Starting process 52233.");
	yall_enable_subsystem("scheduler");

	for (int i = 0; i < 5; ++i)
		pthread_join(threads[i], NULL);

	yall_show_subsystems_tree();

	yall_close();
	yall_close_all();


	return 0;
}

void memoryInfos(struct yall_call_data *d, const void *args)
{
	(void)(args);

	yall_call_add_line(d, 0, "======= Backtrace: =========");
	yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x70bfb)[0x7ff9cd0bfbfb]");
	yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x76fc6)[0x7ff9cd0c5fc6]");
	yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x7780e)[0x7ff9cd0c680e]");
	yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x35940)[0x7ff9cd084940]");
	yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x3599a)[0x7ff9cd08499a]");
	yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf8)[0x7ff9cd06f2e8]");

	yall_call_add_line(d, 0, "======== Memory map: ========");
	yall_call_add_line(d, 1, "55d5e5d8c000-55d5e5dbe000 rw-p 00000000 00:00 0			  [heap]");
	yall_call_add_line(d, 1, "7ff9c8000000-7ff9c8021000 rw-p 00000000 00:00 0 ");
	yall_call_add_line(d, 1, "7ff9c8021000-7ff9cc000000 ---p 00000000 00:00 0 ");
	yall_call_add_line(d, 1, "7ff9cd04f000-7ff9cd1e2000 r-xp 00000000 08:06 4195034		    /lib/x86_64-linux-gnu/libc-2.24.so");
	yall_call_add_line(d, 1, "7ff9cd1e2000-7ff9cd3e2000 ---p 00193000 08:06 4195034		    /lib/x86_64-linux-gnu/libc-2.24.so");
}
