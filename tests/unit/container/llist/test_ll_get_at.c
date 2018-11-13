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
Test(container_llist, test_ll_get_at0)
{
	llist_t *l = ll_new();

	cr_assert_eq(ll_get_at(l, 0), NULL);

	ll_delete(l, NULL);
}

/*
 * Empty list, get last
 */
Test(container_llist, test_ll_get_at1)
{
	llist_t *l = ll_new();

	cr_assert_eq(ll_get_at(l, -1), NULL);

	ll_delete(l, NULL);
}

/*
 * Empty list, get 'middle'
 */
Test(container_llist, test_ll_get_at2)
{
	llist_t *l = ll_new();

	cr_assert_eq(ll_get_at(l, 2), NULL);

	ll_delete(l, NULL);
}

/*
 * Non-empty list, get first
 */
Test(container_llist, test_ll_get_at3)
{
	llist_t *l = test_llist_test_data();

	cr_assert_eq(ll_get_at(l, 0), llist_data[0]->data);

	ll_delete(l, &free);
}

/*
 * Non-empty list, get last
 */
Test(container_llist, test_ll_get_at4)
{
	llist_t *l = test_llist_test_data();

	cr_assert_eq(ll_get_at(l, -1), llist_data[4]->data);

	ll_delete(l, &free);
}

/*
 * Non-empty list, get 'middle'
 */
Test(container_llist, test_ll_get_at5)
{
	llist_t *l = test_llist_test_data();

	cr_assert_eq(ll_get_at(l, 2), llist_data[2]->data);

	ll_delete(l, &free);
}

/*
 * Non-empty list, get bigger than size
 */
Test(container_llist, test_ll_get_at6)
{
	llist_t *l = test_llist_test_data();

	cr_assert_eq(ll_get_at(l, 50), llist_data[4]->data);

	ll_delete(l, &free);
}
