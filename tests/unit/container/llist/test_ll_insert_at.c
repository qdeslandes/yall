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
Test(container_llist, test_ll_insert_at0)
{
	llist_t *l = ll_new();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_at(l, 0, a);
	cr_assert_eq(l->head->data, a);
	cr_assert_eq(l->tail->data, a);
	cr_assert_eq(l->size, 1);

	ll_delete(l, &free);
}

/*
 * Empty list, insert last
 */
Test(container_llist, test_ll_insert_at1)
{
	llist_t *l = ll_new();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_at(l, -1, a);
	cr_assert_eq(l->head->data, a);
	cr_assert_eq(l->tail->data, a);
	cr_assert_eq(l->size, 1);

	ll_delete(l, &free);
}

/*
 * Empty list, insert 'middle'
 */
Test(container_llist, test_ll_insert_at2)
{
	llist_t *l = ll_new();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_at(l, 2, a);
	cr_assert_eq(l->head->data, a);
	cr_assert_eq(l->tail->data, a);
	cr_assert_eq(l->size, 1);

	ll_delete(l, &free);
}

/*
 * Non-empty list, insert first
 */
Test(container_llist, test_ll_insert_at3)
{
	llist_t *l = test_llist_test_data();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_at(l, 0, a);
	cr_assert_eq(l->head->data, a);
	cr_assert_eq(l->head->next, llist_data[0]);
	cr_assert_eq(l->size, 6);

	ll_delete(l, &free);
}

/*
 * Non-empty list, insert last
 */
Test(container_llist, test_ll_insert_at4)
{
	llist_t *l = test_llist_test_data();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_at(l, -1, a);
	cr_assert_eq(l->tail->data, a);
	cr_assert_eq(l->tail->previous, llist_data[4]);
	cr_assert_eq(l->size, 6);

	ll_delete(l, &free);
}

/*
 * Non-empty list, insert 'middle'
 */
Test(container_llist, test_ll_insert_at5)
{
	llist_t *l = test_llist_test_data();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_at(l, 2, a);
	cr_assert_eq(l->head->next->next->data, a);
	cr_assert_eq(l->head->next->next->next, llist_data[2]);
	cr_assert_eq(l->size, 6);

	ll_delete(l, &free);
}

/*
 * Non-empty list, insert bigger than size
 */
Test(container_llist, test_ll_insert_at6)
{
	llist_t *l = test_llist_test_data();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_at(l, 100, a);
	cr_assert_eq(l->tail->data, a);
	cr_assert_eq(l->tail->previous, llist_data[4]);
	cr_assert_eq(l->size, 6);

	ll_delete(l, &free);
}

/*
 * Non-empty list, insert just before the last one
 */
Test(container_llist, test_ll_insert_at7)
{
	llist_t *l = test_llist_test_data();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_at(l, 4, a);
	cr_assert_eq(l->tail->previous->data, a);
	cr_assert_eq(l->tail->previous->next, llist_data[4]);
	cr_assert_eq(l->size, 6);

	ll_delete(l, &free);
}
