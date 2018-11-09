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
 * Empty list, insert last
 */
Test(container_llist, test_ll_insert_last0)
{
	llist_t *l = ll_new();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_last(l, a);
	cr_assert_eq(l->head->data, a);
	cr_assert_eq(l->tail->data, a);
	cr_assert_eq(l->size, 1);

	free(l);
	free(a);
}

/*
 * Non-empty list, insert last
 */
Test(container_llist, test_ll_insert_last1)
{
	llist_t *l = test_llist_test_data();
	CREATE_LLIST_DATA(a, 1, 2, 3);

	ll_insert_last(l, a);
	cr_assert_eq(l->tail->data, a);
	cr_assert_eq(l->tail->previous, llist_data[4]);
	cr_assert_eq(l->size, 6);

	ll_delete(l, &free);
}
