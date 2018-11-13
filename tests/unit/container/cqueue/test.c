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

#include "container/cqueue/test.h"

struct test_cqueue_node_data *cq_nodes[3] = { 0 };

static void tests_container_cqueue_setup(void)
{

}

static void tests_container_cqueue_clean(void)
{

}

TestSuite(container_cqueue, .init=tests_container_cqueue_setup, .fini=tests_container_cqueue_clean);

void test_cqueue_node_data_deleter(void *data)
{
	free(data);
}

cqueue_t *test_cqueue_empty_queue(void)
{
	return cq_new();
}

cqueue_t *test_cqueue_queue(void)
{
	cqueue_t *q = cq_new();

	CREATE_NODE(a, 0, 1, 2);
	CREATE_NODE(b, 3, 4, 5);
	CREATE_NODE(c, 6, 7, 8);

	cq_nodes[0] = a;
	cq_nodes[1] = b;
	cq_nodes[2] = c;

	cq_enqueue(q, a);
	cq_enqueue(q, b);
	cq_enqueue(q, c);

	return q;
}
