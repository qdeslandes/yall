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
 * Empty list
 */
Test(container_llist, test_ll_remove_node_at0)
{
	llist_t *l = ll_new();

	cr_assert_eq(ll_remove_node_at(l, 0), NULL);
	cr_assert_eq(ll_remove_node_at(l, -1), NULL);
	cr_assert_eq(ll_remove_node_at(l, 10), NULL);

	free(l);
}

/*
 * Non-empty list, get first
 */
Test(container_llist, test_ll_remove_node_at1)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_remove_node_at(l, 0);
	cr_assert_eq(n, llist_data[0]);
	cr_assert_eq(l->head, llist_data[1]);
	cr_assert_eq(l->head->previous, NULL);

	test_llist_free_data(l);
}

/*
 * Non-empty list, get last
 */
Test(container_llist, test_ll_remove_node_at2)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_remove_node_at(l, -1);
	cr_assert_eq(n, llist_data[4]);
	cr_assert_eq(l->tail, llist_data[3]);
	cr_assert_eq(l->tail->next, NULL);

	test_llist_free_data(l);
}

/*
 * Non-empty list, get element
 */
Test(container_llist, test_ll_remove_node_at3)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_remove_node_at(l, 1);
	cr_assert_eq(n, llist_data[1]);
	cr_assert_eq(l->head, llist_data[0]);
	cr_assert_eq(l->head->next, llist_data[2]);
	cr_assert_eq(l->head->next->previous, llist_data[0]);

	test_llist_free_data(l);
}

/*
 * Non-empty list, get index bigger than size
 */
Test(container_llist, test_ll_remove_node_at4)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_remove_node_at(l, 100);
	cr_assert_eq(n, llist_data[4]);
	cr_assert_eq(l->tail, llist_data[3]);
	cr_assert_eq(l->tail->next, NULL);

	test_llist_free_data(l);
}
