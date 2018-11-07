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

#include "queue/test.h"

/*
 * O.K.
 * NULL queue
 */
Test(queue, test_queue_reverse0)
{
	cr_assert_eq(queue_reverse(NULL), NULL);
}

/*
 * O.K.
 * Non-NULL queue
 */
Test(queue, test_queue_reverse1)
{
	struct qnode q0 = { NULL, NULL };
	struct qnode q1 = { &q0, NULL };
	struct qnode q2 = { &q1, NULL };

	struct qnode *r = queue_reverse(&q2);

	cr_assert_eq(r, &q0);
	cr_assert_eq(r->next, &q1);
	cr_assert_eq(r->next->next, &q2);
}
