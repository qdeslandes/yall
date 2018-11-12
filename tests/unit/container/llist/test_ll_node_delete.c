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

#include "container/llist/test.h"

/*
 * Without data, without deleter
 */
Test(container_llist, test_ll_node_delete0)
{
	llist_node_t *n = ll_node_new(NULL);
	
	void *data = ll_node_delete(n, NULL);

	cr_assert_eq(data, NULL);
}

/*
 * Without data, with deleter
 */
Test(container_llist, test_ll_node_delete1)
{
	llist_node_t *n = ll_node_new(NULL);
	
	void *data = ll_node_delete(n, &test_llist_data_deleter);

	cr_assert_eq(data, NULL);
}

/*
 * With data, without deleter
 */
Test(container_llist, test_ll_node_delete2)
{
	struct test_llist_data *data = test_llist_get_fake_data(0, 1, 2);
	llist_node_t *n = ll_node_new(data);
	
	struct test_llist_data *deleted_data = ll_node_delete(n, NULL);

	cr_assert_eq(deleted_data, data);
	cr_assert_eq(deleted_data->a, 0);
	cr_assert_eq(deleted_data->b, 1);
	cr_assert_eq(deleted_data->c, 2);
}

/*
 * With data, with deleter
 */
Test(container_llist, test_ll_node_delete3)
{
	struct test_llist_data *data = test_llist_get_fake_data(0, 1, 2);
	llist_node_t *n = ll_node_new(data);
	
	struct test_llist_data *deleted_data = ll_node_delete(n, &test_llist_data_deleter);

	cr_assert_eq(deleted_data, NULL);
}
