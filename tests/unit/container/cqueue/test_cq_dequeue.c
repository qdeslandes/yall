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
 * Dequeue empty queue
 */
Test(container_cqueue, test_cq_dequeue0)
{
	cqueue_t *q = test_cqueue_empty_queue();

	cr_assert_eq(cq_dequeue(q), NULL);
}

/*
 * Dequeue non-empty queue
 */
Test(container_cqueue, test_cq_dequeue1)
{
	cqueue_t *q = test_cqueue_queue();
	struct test_cqueue_node_data *a = NULL;

	a = cq_dequeue(q);
	cr_assert_eq(a, cq_nodes[2]);

	a = cq_dequeue(q);
	cr_assert_eq(a, cq_nodes[1]);

	a = cq_dequeue(q);
	cr_assert_eq(a, cq_nodes[0]);

	a = cq_dequeue(q);
	cr_assert_eq(a, NULL);

	cq_delete(q, NULL);
}
