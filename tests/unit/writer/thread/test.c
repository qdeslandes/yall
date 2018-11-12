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

#include "yall/container/cqueue.h"

static void tests_writer_thread_setup(void)
{
	cr_redirect_stderr();
}

static void tests_writer_thread_clean(void)
{

}

TestSuite(writer_thread, .init=tests_writer_thread_setup, .fini=tests_writer_thread_clean);

cqueue_t *test_message_queue(void)
{
	cqueue_t *q = cq_new();

	CREATE_MESSAGE(a, "hello");
	cq_enqueue(q, a);

	CREATE_MESSAGE(b, "1337");
	cq_enqueue(q, b);

	CREATE_MESSAGE(c, "world");
	cq_enqueue(q, c);

	return q;
}
