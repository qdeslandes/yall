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
 * Without data
 */
Test(container_cqueue, test_cq_node_new0)
{
	cqueue_node_t *n = cq_node_new(NULL);

	cr_assert(n);

	cq_node_delete(n, NULL);
}

/*
 * With data
 */
Test(container_cqueue, test_cq_node_new1)
{
	void *data = malloc(3);
	cqueue_node_t *n = cq_node_new(data);

	cr_assert(n);

	cq_node_delete(n, NULL);
}
