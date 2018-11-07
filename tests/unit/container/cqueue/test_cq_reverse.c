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

/*
 * Empty queue
 */
Test(container_cqueue, test_cq_reverse0)
{
	cqueue_t *q = test_cqueue_empty_queue();

	cr_assert_eq(cq_dequeue(q), NULL);
	cq_reverse(q);
	cr_assert_eq(cq_dequeue(q), NULL);

	cq_delete(q, NULL);
}

/*
 * 1 element in queue
 */
Test(container_cqueue, test_cq_reverse1)
{
	cqueue_t *q = test_cqueue_empty_queue();

	CREATE_NODE(data, 10, 20, 30);
	cq_enqueue(q, data);

	cq_reverse(q);
	cr_assert_eq(cq_dequeue(q), data);
	free(data);
	cr_assert_eq(cq_dequeue(q), NULL);

	cq_delete(q, NULL);
}

/*
 * Multiple elements in queue
 */
Test(container_cqueue, test_cq_reverse2)
{
	cqueue_t *q = test_cqueue_queue();
	struct test_cqueue_node_data *data = NULL;

	cq_reverse(q);

	data = cq_dequeue(q);
	cr_assert_eq(cq_nodes[0], data);
	free(data);

	data = cq_dequeue(q);
	cr_assert_eq(cq_nodes[1], data);
	free(data);
	
	data = cq_dequeue(q);
	cr_assert_eq(cq_nodes[2], data);
	free(data);

	cr_assert_eq(cq_dequeue(q), NULL);

	cq_delete(q, NULL);
}
