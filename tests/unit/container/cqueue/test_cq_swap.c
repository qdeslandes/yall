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
Test(container_cqueue, test_cq_swap0)
{
	cqueue_t *q0 = test_cqueue_empty_queue();
	cqueue_t *q1 = NULL;

	q1 = cq_swap(q0);

	cr_assert_eq(cq_dequeue(q0), NULL);
	cr_assert_eq(q1, NULL);

	cq_delete(q0, NULL);
}

/*
 * 1 element in queue
 */
Test(container_cqueue, test_cq_swap1)
{
	cqueue_t *q0 = test_cqueue_empty_queue();
	cqueue_t *q1 = NULL;

	CREATE_NODE(a, 10, 20, 30);
	cq_enqueue(q0, a);

	q1 = cq_swap(q0);

	cr_assert_eq(cq_dequeue(q0), NULL);
	cr_assert_eq(cq_dequeue(q1), a);
	free(a);

	cq_delete(q0, NULL);
	cq_delete(q1, NULL);
}

/*
 * Multiple elements in queue
 */
Test(container_cqueue, test_cq_swap2)
{
	cqueue_t *q0 = test_cqueue_queue();
	cqueue_t *q1 = NULL;

	q1 = cq_swap(q0);

	cr_assert_eq(cq_dequeue(q0), NULL);
	cr_assert_eq(cq_dequeue(q1), nodes[0]);
	free(nodes[0]);

	cr_assert_eq(cq_dequeue(q1), nodes[1]);
	free(nodes[1]);

	cr_assert_eq(cq_dequeue(q1), nodes[2]);
	free(nodes[2]);

	cq_delete(q0, NULL);
	cq_delete(q1, NULL);
}
