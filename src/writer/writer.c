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

#include "yall/writer/writer.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include "yall/container/cqueue.h"
#include "yall/error.h"
#include "yall/writer/thread.h"
#include "yall/utils.h"
#include "yall/writer/console.h"
#include "yall/writer/file.h"
#include "yall/debug.h"
#include "yall/queue.h"

static cqueue_t *msg_queue = NULL;

yall_error writer_init(uint16_t frequency)
{
	yall_error ret = YALL_SUCCESS;

	msg_queue = cq_new();

	ret = start_thread(frequency, msg_queue);

	return ret;
}

void write_msg(struct message *m)
{
	cq_enqueue(msg_queue, m);
}

void writer_close(void)
{
	stop_thread();

	cq_delete(msg_queue, NULL);
}
