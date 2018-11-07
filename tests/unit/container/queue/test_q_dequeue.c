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

#include "container/queue/test.h"

/*
 * Dequeue empty queue
 */
Test(container_queue, test_q_dequeue0)
{
	queue_t *q = test_queue_empty_queue();

	cr_assert_eq(q_dequeue(q), NULL);
}

/*
 * Dequeue non-empty queue
 */
Test(container_queue, test_q_dequeue1)
{
	queue_t *q = test_queue_queue();
	struct test_queue_data *a = NULL;

	a = q_dequeue(q);
	cr_assert_eq(a, q_nodes[0]);

	a = q_dequeue(q);
	cr_assert_eq(a, q_nodes[1]);

	a = q_dequeue(q);
	cr_assert_eq(a, q_nodes[2]);

	a = q_dequeue(q);
	cr_assert_eq(a, NULL);

	q_delete(q, NULL);
}
