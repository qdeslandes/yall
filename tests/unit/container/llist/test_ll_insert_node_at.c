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
 * Empty list, insert first
 */
Test(container_llist, test_ll_insert_node_at0)
{
	llist_t *l = ll_new();

	llist_node_t *n = ll_node_new(NULL);

	ll_insert_node_at(l, 0, n);
	cr_assert_eq(l->head, n);
	cr_assert_eq(l->tail, n);
	cr_assert_eq(l->size, 1);

	free(l);
	free(n);
}

/*
 * Empty list, insert last
 */
Test(container_llist, test_ll_insert_node_at1)
{
	llist_t *l = ll_new();

	llist_node_t *n = ll_node_new(NULL);

	ll_insert_node_at(l, -1, n);
	cr_assert_eq(l->head, n);
	cr_assert_eq(l->tail, n);
	cr_assert_eq(l->size, 1);

	free(l);
	free(n);
}

/*
 * Empty list, insert 'middle'
 */
Test(container_llist, test_ll_insert_node_at2)
{
	llist_t *l = ll_new();

	llist_node_t *n = ll_node_new(NULL);

	ll_insert_node_at(l, 3, n);
	cr_assert_eq(l->head, n);
	cr_assert_eq(l->tail, n);
	cr_assert_eq(l->size, 1);

	free(l);
	free(n);
}

/*
 * Non-empty list, insert first
 */
Test(container_llist, test_ll_insert_node_at3)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_node_new(NULL);

	ll_insert_node_at(l, 0, n);
	cr_assert_eq(l->head, n);
	cr_assert_eq(l->head->next, llist_data[0]);
	cr_assert_eq(l->size, 6);

	test_llist_free_data(l);
	free(n);
}

/*
 * Non-empty list, insert last
 */
Test(container_llist, test_ll_insert_node_at4)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_node_new(NULL);

	ll_insert_node_at(l, -1, n);
	cr_assert_eq(l->tail, n);
	cr_assert_eq(l->tail->previous, llist_data[4]);
	cr_assert_eq(l->size, 6);

	test_llist_free_data(l);
	free(n);
}

/*
 * Non-empty list, insert 'middle'
 */
Test(container_llist, test_ll_insert_node_at5)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_node_new(NULL);

	ll_insert_node_at(l, 2, n);
	cr_assert_eq(llist_data[1]->next, n);
	cr_assert_eq(n->previous, llist_data[1]);
	cr_assert_eq(n->next, llist_data[2]);
	cr_assert_eq(llist_data[2]->previous, n);
	cr_assert_eq(l->size, 6);

	test_llist_free_data(l);
	free(n);
}

/*
 * Non-empty list, insert bigger than size
 */
Test(container_llist, test_ll_insert_node_at6)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_node_new(NULL);

	ll_insert_node_at(l, 100, n);
	cr_assert_eq(l->tail, n);
	cr_assert_eq(l->tail->previous, llist_data[4]);
	cr_assert_eq(l->size, 6);

	test_llist_free_data(l);
	free(n);
}

/*
 * Non-empty list, insert just before the last one
 */
Test(container_llist, test_ll_insert_node_at7)
{
	llist_t *l = test_llist_test_data();

	llist_node_t *n = ll_node_new(NULL);

	ll_insert_node_at(l, 4, n);
	cr_assert_eq(llist_data[3]->next, n);
	cr_assert_eq(n->previous, llist_data[3]);
	cr_assert_eq(n->next, llist_data[4]);
	cr_assert_eq(llist_data[4]->previous, n);
	cr_assert_eq(l->tail, llist_data[4]);
	cr_assert_eq(l->size, 6);

	test_llist_free_data(l);
	free(n);
}

/*
 * Add last 2 times in a row (was buggy)
 */
Test(container_llist, test_ll_insert_node_at8)
{
	llist_t *l = ll_new();

	llist_node_t *n0 = ll_node_new(NULL);
	llist_node_t *n1 = ll_node_new(NULL);

	ll_insert_node_at(l, -1, n0);
	ll_insert_node_at(l, -1, n1);

	cr_assert_eq(l->head, n0);
	cr_assert_eq(l->tail, n1);
	cr_assert_eq(l->head->next, n1);

	ll_delete(l, NULL);
}

/*
 * Add first 2 times in a row (was buggy)
 */
Test(container_llist, test_ll_insert_node_at9)
{
	llist_t *l = ll_new();

	llist_node_t *n0 = ll_node_new(NULL);
	llist_node_t *n1 = ll_node_new(NULL);

	ll_insert_node_at(l, 0, n0);
	ll_insert_node_at(l, 0, n1);

	cr_assert_eq(l->head, n1);
	cr_assert_eq(l->tail, n0);
	cr_assert_eq(l->head->next, n0);

	ll_delete(l, NULL);
}
