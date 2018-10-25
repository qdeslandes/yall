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

#include "yall/writer/thread.h"

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "yall/debug.h"
#include "yall/error.h"
#include "yall/queue.h"
#include "yall/output/types.h"
#include "yall/message.h"
#include "yall/writer/file.h"
#include "yall/writer/console.h"

#ifdef __linux__
#	include <stdatomic.h>
#	include <unistd.h>
#	define yall_sleep(ms) usleep(ms * 1000)
static atomic_bool thread_run = true;
#elif _WIN32
#	include <Windows.h>
#	define yall_sleep(ms) Sleep(ms)
static __declspec(align(64)) bool thread_run = true;
#endif

/*
 * This should ensure atomicity of read / write on the variable. But, as
 * Chris Hanson mention here https://goo.gl/qc3g9E, there is many factors to
 * check to be sure this will work. So, this is not sufficient, but... This
 * variable is not business critical.
 * Also, Intel assumes reading / writing a 64 bits aligned variable is thread
 * safe : https://goo.gl/HW5oua.
 * See also : https://goo.gl/4DzPyx.
 */

static uint16_t thread_frequency;
static pthread_t thread;
static void *writer_thread(void *args);

uint8_t start_thread(uint16_t frequency)
{
	uint8_t ret = YALL_SUCCESS;

	thread_run = true;
	thread_frequency = frequency;

	int thread_ret = pthread_create(&thread, NULL, writer_thread, NULL);

	if (thread_ret != 0)
		ret = YALL_CANT_CREATE_THREAD;

	return ret;
}

void stop_thread(void)
{
	thread_run = false;
	pthread_join(thread, NULL);
}

/**
 * \brief This function is used to write all the message from the given queue,
 *	through all writer function (write_log_console(), write_log_file(),
 *	...). The given message queue must be reversed as, for concurrency
 *	purposes, we can't enqueue message in the proper order. Thus, is the
 *	queue is not reversed, the messages will be printed in reversed order.
 *	Once the given queue has been wrote, it is freed.
 * \param msg_queue List of messages queue to write.
 */
static void write_queue_messages(struct qnode *msg_queue)
{
	struct qnode *node_next = NULL;
	struct message *m = NULL;

	if (! msg_queue)
		return;

	msg_queue = queue_reverse(msg_queue);

	while (msg_queue) {
		node_next = msg_queue->next;
		m = msg_queue->data;

		if (yall_console_output & m->output_type)
			write_log_console(m->log_level, m->data);

		if (yall_file_output & m->output_type)
			write_log_file(m->file.filename, m->data);

		if (yall_syslog_output & m->output_type)
			write_log_syslog(m->log_level, m->data);

		qnode_delete(msg_queue, message_delete_wrapper);

		msg_queue = node_next;
	}
}

/**
 * \brief Main function of the writer threader. It loops at >thread_frequency>
 *	Hz. Messages queue is swapped on each loop, wrote and deleted.
 *	Once the library is closed, *thread_run* is set to false and the thread
 *	stop when the messages queue has been wrote a last time.
 * \param args Arguments to use inside the thread, required by pthread but
 *	unused.
 */
static void *writer_thread(void *args)
{
	UNUSED(args);

	int loop_duration_ms = (int)((1.0 / thread_frequency) * 1000.0);

	while (thread_run) {
		clock_t begin = clock();

		struct qnode *msg_queue = swap_queue();

		write_queue_messages(msg_queue);

		uint32_t wait_ms = (uint32_t)(loop_duration_ms -
			((clock() - begin) / CLOCKS_PER_SEC) * 1000);
		yall_sleep(wait_ms);
	}

	/*
	 * Not the cleanest way to do this, but this line allow to write the
	 * remaining log message added to the queue between swap_queue() and
	 * the beginning of the loop. This way, all the log message added
	 * between swap_queue() and thread_run = false assignation are
	 * displayed.
	 */
	write_queue_messages(swap_queue());

	// When execution is here, the queue's head should be equal to NULL.

	return NULL;
}
