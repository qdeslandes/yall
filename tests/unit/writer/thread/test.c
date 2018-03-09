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

#include "writer/thread/test.h"

static void tests_writer_thread_setup(void)
{
	cr_redirect_stderr();
}

static void tests_writer_thread_clean(void)
{

}

TestSuite(writer_thread, .init=tests_writer_thread_setup, .fini=tests_writer_thread_clean);

struct qnode *test_msg_queue = NULL;
struct qnode *test_msg_queue_array[3] = { NULL };

void test_start_thread(void)
{
	start_thread(60);
}

void test_stop_thread(void)
{
	stop_thread();
}

void test_create_msg_queue(void)
{
	struct yall_subsystem_params con_p = { yall_debug, yall_subsys_enable, yall_console_output, { 0 }, { NULL } };
	struct message *con_m = message_new(strdup("console_output"), yall_debug, &con_p);
	struct qnode *con_n = qnode_new(con_m);

	struct yall_subsystem_params file_p = { yall_debug, yall_subsys_enable, yall_file_output, { 0 }, { strdup("./yall.log") } };
	struct message *file_m = message_new(strdup("file_output"), yall_debug, &file_p);
	struct qnode *file_n = qnode_new(file_m);

	struct yall_subsystem_params slog_p = { yall_debug, yall_subsys_enable, yall_syslog_output, { 0 }, { NULL } };
	struct message *slog_m = message_new(strdup("syslog_output"), yall_debug, &slog_p);
	struct qnode *slog_n = qnode_new(slog_m);

	test_msg_queue = con_n;
	con_n->next = file_n;
	file_n->next = slog_n;

	test_msg_queue_array[0] = con_n;
	test_msg_queue_array[1] = file_n;
	test_msg_queue_array[2] = slog_n;
}

void test_delete_msg_queue(void)
{
	qnode_delete(test_msg_queue_array[0], message_delete_wrapper);
	test_msg_queue_array[0] = NULL;

	qnode_delete(test_msg_queue_array[1], message_delete_wrapper);
	test_msg_queue_array[1] = NULL;

	qnode_delete(test_msg_queue_array[2], message_delete_wrapper);
	test_msg_queue_array[2] = NULL;
}
