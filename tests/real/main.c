#include <stdio.h>

#include <stdbool.h>
#include <pthread.h>
#include <yall/yall.h>

#define N_THREADS	10

static __declspec(align(64)) bool thread_run = true;

void *t0(void *args)
{
	while (thread_run) {
		YALL_INFO("t0", "Thread 0 message.");

		Sleep(10);
	}

	return NULL;
}

void *t1(void *args)
{
	while (thread_run) {
		YALL_WARNING("t1", "Thread 1 message.");

		Sleep(10);
	}

	return NULL;
}

void *t2(void *args)
{
	while (thread_run) {
		YALL_ERR("t2", "Thread 2 message.");

		Sleep(10);
	}

	return NULL;
}

void *t3(void *args)
{
	while (thread_run) {
		YALL_ERR("t3", "Thread 3 message.");

		Sleep(10);
	}

	return NULL;
}

void *t4(void *args)
{
	while (thread_run) {
		YALL_ERR("t4", "Thread 4 message.");

		Sleep(10);
	}

	return NULL;
}

void *t5(void *args)
{
	while (thread_run) {
		YALL_ERR("t5", "Thread 5 message.");

		Sleep(10);
	}

	return NULL;
}

void *t6(void *args)
{
	while (thread_run) {
		YALL_ERR("t6", "Thread 6 message.");

		Sleep(10);
	}

	return NULL;
}

void *t7(void *args)
{
	while (thread_run) {
		YALL_ERR("t7", "Thread 7 message.");

		Sleep(10);
	}

	return NULL;
}

void *t8(void *args)
{
	while (thread_run) {
		YALL_ERR("t8", "Thread 8 message.");

		Sleep(10);
	}

	return NULL;
}

void *t9(void *args)
{
	while (thread_run) {
		YALL_ERR("t9", "Thread 9 message.");

		Sleep(10);
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
	yall_set_subsystem("t0", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t1", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t2", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t3", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t4", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t5", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t6", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t7", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t8", "YALLreal", yall_debug, yall_console_output, NULL);
	yall_set_subsystem("t9", "YALLreal", yall_debug, yall_console_output, NULL);

	YALL_INFO("setup", "Starting threads.");

	for (int i = 0; i < N_THREADS; ++i) {
		int ret = pthread_create(&threads[0], NULL, tfunc[i], NULL);
		if (ret != 0)
			YALL_ERR("setup", "Thread %d startup failed.", i);
	}

	YALL_INFO("setup", "Threads running, hit a key to stop.");

#ifdef _WIN32
	getchar();
#endif

	YALL_INFO("setup", "Closing threads.");

	thread_run = false;
	for (int i = 0; i < N_THREADS; ++i)
		pthread_join(threads[i], NULL);

	yall_close();

	printf("Threads stopped, hit a key to quit...\n");

#ifdef _WIN32
	getchar();
#endif

	return 0;
}
