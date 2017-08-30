#include <stdio.h>

#include <stdbool.h>
#include <pthread.h>
#include <yall/yall.h>

#define N_THREADS	10

#ifdef __linux__
#define yall_sleep(ms) usleep(ms * 1000)
static bool thread_run __attribute__((aligned(64))) = true;
#elif _WIN32
static __declspec(align(64)) bool thread_run = true;
#define yall_sleep(ms) Sleep(ms)
#endif

void *t0(void *args)
{
	while (thread_run) {
		YALL_INFO("t0", "Thread 0 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t1(void *args)
{
	while (thread_run) {
		YALL_WARNING("t1", "Thread 1 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t2(void *args)
{
	while (thread_run) {
		YALL_ERR("t2", "Thread 2 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t3(void *args)
{
	while (thread_run) {
		YALL_ERR("t3", "Thread 3 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t4(void *args)
{
	while (thread_run) {
		YALL_ERR("t4", "Thread 4 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t5(void *args)
{
	while (thread_run) {
		YALL_ERR("t5", "Thread 5 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t6(void *args)
{
	while (thread_run) {
		YALL_ERR("t6", "Thread 6 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t7(void *args)
{
	while (thread_run) {
		YALL_ERR("t7", "Thread 7 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t8(void *args)
{
	while (thread_run) {
		YALL_ERR("t8", "Thread 8 message.");

		yall_sleep(10);
	}

	return NULL;
}

void *t9(void *args)
{
	while (thread_run) {
		YALL_ERR("t9", "Thread 9 message.");

		yall_sleep(10);
	}

	return NULL;
}

static pthread_t threads[N_THREADS];
static void *(*tfunc[N_THREADS])(void *) = { t0, t1, t2, t3 ,t4, t5, t6, t7, t8, t9 };

int main(void)
{
	yall_init();

	yall_set_subsystem("YALLreal", NULL, yall_debug, yall_console_output, NULL);
	yall_set_subsystem("setup", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("threads", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t0", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t1", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t2", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t3", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t4", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t5", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t6", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t7", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t8", "threads", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t9", "threads", yall_debug, yall_console_output, NULL);

	yall_disable_subsystem("threads");

	YALL_INFO("setup", "Starting threads.");

	for (int i = 0; i < N_THREADS; ++i) {
		int ret = pthread_create(&threads[0], NULL, tfunc[i], NULL);
		if (ret != 0)
			YALL_ERR("setup", "Thread %d startup failed.", i);
		else
			YALL_INFO("setup", "Thread %d started.", i);
	}

	YALL_INFO("setup", "Threads running, hit a key to stop.");

	getchar();

	YALL_INFO("setup", "Closing threads.");

	thread_run = false;

	for (int i = 0; i < N_THREADS; ++i)
		pthread_join(threads[i], NULL);

	yall_close();

	printf("Threads stopped, hit a key to quit...\n");

	getchar();

	return 0;
}
