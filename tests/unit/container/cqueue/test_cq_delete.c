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
 * No nodes, no deleter
 */
Test(container_cqueue, test_cq_delete0)
{
	cq_delete(test_cqueue_empty_queue(), NULL);

	cr_assert(1);
}

/*
 * No nodes, deleter
 */
Test(container_cqueue, test_cq_delete1)
{
	cq_delete(test_cqueue_empty_queue(), &test_cqueue_node_data_deleter);

	cr_assert(1);
}

/*
 * Nodes, no deleter
 */
Test(container_cqueue, test_cq_delete2)
{
	cq_delete(test_cqueue_queue(), NULL);

	cr_assert(1);
}

/*
 * Nodes, deleter
 */
Test(container_cqueue, test_cq_delete3)
{
	cq_delete(test_cqueue_queue(), &test_cqueue_node_data_deleter);

	cr_assert(1);
}
