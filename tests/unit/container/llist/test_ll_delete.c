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
 * Empty list, no deleter
 */
Test(container_llist, test_ll_delete0)
{
	llist_t *n = ll_new();
	
	ll_delete(n, NULL);

	cr_assert(1);
}

/*
 * Empty list, deleter
 */
Test(container_llist, test_ll_delete1)
{
	llist_t *n = ll_new();
	
	ll_delete(n, &free);

	cr_assert(1);
}

/*
 * Non-empty list, no deleter
 */
Test(container_llist, test_ll_delete2)
{
	struct test_llist_test_data *data[5] = { 0 };
	llist_t *n = test_llist_test_data();
	
	for (int i = 0; i < 5; ++i)
		data[i] = llist_data[i]->data;
	
	ll_delete(n, NULL);

	cr_assert(1);

	for (int i = 0; i < 5; ++i)
		free(data[i]);
}

/*
 * Non-empty list, deleter
 */
Test(container_llist, test_ll_delete3)
{
	llist_t *n = test_llist_test_data();
	
	ll_delete(n, &free);

	cr_assert(1);
}
