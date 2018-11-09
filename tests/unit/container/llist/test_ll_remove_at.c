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
 * Empty list, get first
 */
Test(container_llist, test_ll_remove_at0)
{
	llist_t *l = ll_new();

	cr_assert_eq(l->size, 0);
	cr_assert_eq(ll_remove_at(l, 0), NULL);

	ll_delete(l, NULL);
}

/*
 * Empty list, get last
 */
Test(container_llist, test_ll_remove_at1)
{
	llist_t *l = ll_new();

	cr_assert_eq(ll_remove_at(l, -1), NULL);
	cr_assert_eq(l->size, 0);

	ll_delete(l, NULL);
}

/*
 * Empty list, get 'middle'
 */
Test(container_llist, test_ll_remove_at2)
{
	llist_t *l = ll_new();

	cr_assert_eq(ll_remove_at(l, 2), NULL);
	cr_assert_eq(l->size, 0);

	ll_delete(l, NULL);
}

/*
 * Non-empty list, get first
 */
Test(container_llist, test_ll_remove_at3)
{
	llist_t *l = test_llist_test_data();
	struct test_llist_data *d = NULL;

	d = ll_remove_at(l, 0);
	cr_assert(d);
	cr_assert_eq(l->head, llist_data[1]);
	cr_assert_eq(l->size, 4);

	free(d);
	ll_delete(l, &free);
}

/*
 * Non-empty list, get last
 */
Test(container_llist, test_ll_remove_at4)
{
	llist_t *l = test_llist_test_data();
	struct test_llist_data *d = NULL;

	d = ll_remove_at(l, -1);
	cr_assert(d);
	cr_assert_eq(l->tail, llist_data[3]);
	cr_assert_eq(l->size, 4);

	free(d);
	ll_delete(l, &free);
}

/*
 * Non-empty list, get 'middle'
 */
Test(container_llist, test_ll_remove_at5)
{
	llist_t *l = test_llist_test_data();
	struct test_llist_data *d = NULL;

	d = ll_remove_at(l, 2);
	cr_assert(d);
	cr_assert_eq(llist_data[1]->next, llist_data[3]);
	cr_assert_eq(llist_data[3]->previous, llist_data[1]);
	cr_assert_eq(l->size, 4);

	free(d);
	ll_delete(l, &free);
}

/*
 * Non-empty list, get bigger than size
 */
Test(container_llist, test_ll_remove_at6)
{
	llist_t *l = test_llist_test_data();
	struct test_llist_data *d = NULL;

	d = ll_remove_at(l, 100);
	cr_assert(d);
	cr_assert_eq(l->tail, llist_data[3]);
	cr_assert_eq(l->size, 4);

	free(d);
	ll_delete(l, &free);
}
