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
 * No nodes, insert 1 data
 */
Test(container_queue, test_q_enqueue0)
{
	queue_t *q = test_queue_empty_queue();
	struct test_queue_data *data = NULL;

	CREATE_QUEUE_DATA(a, 10, 20, 30);

	q_enqueue(q, a);

	data = q_dequeue(q);
	cr_assert_eq(data, a);
	cr_assert_eq(data->a, 10);
	cr_assert_eq(data->b, 20);
	cr_assert_eq(data->c, 30);

	free(data);

	q_delete(q, NULL);
}

/*
 * No nodes, insert multiple data
 */
Test(container_queue, test_q_enqueue1)
{
	queue_t *q = test_queue_empty_queue();
	struct test_queue_data *data = NULL;

	CREATE_QUEUE_DATA(a, 3, 7, 11);
	CREATE_QUEUE_DATA(b, 13, 17, 19);

	q_enqueue(q, a);
	q_enqueue(q, b);

	data = q_dequeue(q);
	cr_assert_eq(data, a);
	cr_assert_eq(data->a, 3);
	cr_assert_eq(data->b, 7);
	cr_assert_eq(data->c, 11);
	free(data);

	data = q_dequeue(q);
	cr_assert_eq(data, b);
	cr_assert_eq(data->a, 13);
	cr_assert_eq(data->b, 17);
	cr_assert_eq(data->c, 19);
	free(data);

	q_delete(q, NULL);
}

/*
 * No nodes, insert 1 data, remove it (so queue is empty) and insert back
 */
Test(container_queue, test_q_enqueue2)
{
	queue_t *q = test_queue_empty_queue();
	struct test_queue_data *data = NULL;

	CREATE_QUEUE_DATA(a, 3, 7, 11);

	q_enqueue(q, a);

	data = q_dequeue(q);
	cr_assert_eq(data, a);
	cr_assert_eq(data->a, 3);
	cr_assert_eq(data->b, 7);
	cr_assert_eq(data->c, 11);
	
	q_enqueue(q, data);
	data = q_dequeue(q);
	cr_assert_eq(data, a);
	cr_assert_eq(data->a, 3);
	cr_assert_eq(data->b, 7);
	cr_assert_eq(data->c, 11);
	free(data);

	q_delete(q, NULL);
}

/*
 * Nodes available, insert 1 data
 */
Test(container_queue, test_q_enqueue3)
{
	queue_t *q = test_queue_empty_queue();
	struct test_queue_data *data = NULL;

	CREATE_QUEUE_DATA(a, 3, 7, 11);

	q_enqueue(q, a);

	// Here, as the queue is not reversed, we read the last element inserted
	data = q_dequeue(q);
	cr_assert_eq(data, a);
	cr_assert_eq(data->a, 3);
	cr_assert_eq(data->b, 7);
	cr_assert_eq(data->c, 11);

	free(data);

	q_delete(q, NULL);
}

/*
 * Nodes available, insert multiple data
 */
Test(container_queue, test_q_enqueue4)
{
	queue_t *q = test_queue_empty_queue();
	struct test_queue_data *data = NULL;

	CREATE_QUEUE_DATA(a, 3, 7, 11);
	CREATE_QUEUE_DATA(b, 13, 17, 19);

	q_enqueue(q, a);
	q_enqueue(q, b);

	data = q_dequeue(q);
	cr_assert_eq(data, a);
	cr_assert_eq(data->a, 3);
	cr_assert_eq(data->b, 7);
	cr_assert_eq(data->c, 11);
	free(data);

	data = q_dequeue(q);
	cr_assert_eq(data, b);
	cr_assert_eq(data->a, 13);
	cr_assert_eq(data->b, 17);
	cr_assert_eq(data->c, 19);
	free(data);

	q_delete(q, NULL);
}
