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

llist_node_t *llist_data[5] = { 0 };

static void tests_container_llist_setup(void)
{

}

static void tests_container_llist_clean(void)
{

}

TestSuite(container_llist, .init=tests_container_llist_setup, .fini=tests_container_llist_clean);

void test_llist_data_deleter(void *data)
{
	free(data);
}

struct test_llist_data *test_llist_get_fake_data(int a, int b, int c)
{
	struct test_llist_data *d = malloc(sizeof(struct test_llist_data));

	d->a = a;
	d->b = b;
	d->c = c;

	return d;
}

llist_t *test_llist_test_data(void)
{
	llist_t *l = ll_new();

	CREATE_LLIST_DATA(a, 0, 1, 2);
	llist_data[0] = ll_node_new(a);

	CREATE_LLIST_DATA(b, 3, 4, 5);
	llist_data[1] = ll_node_new(b);

	CREATE_LLIST_DATA(c, 6, 7, 8);
	llist_data[2] = ll_node_new(c);

	CREATE_LLIST_DATA(d, 9, 10, 11);
	llist_data[3] = ll_node_new(d);

	CREATE_LLIST_DATA(e, 12, 13, 14);
	llist_data[4] = ll_node_new(e);

	l->size = 5;
	l->head = llist_data[0];
	l->tail = llist_data[4];

	SET_LLIST_CHAIN(llist_data[0], llist_data[1], llist_data[2]);
	SET_LLIST_CHAIN(llist_data[2], llist_data[3], llist_data[4]);

	return l;
}

void test_llist_free_data(llist_t *l)
{
	ll_node_delete(llist_data[0], &free);
	ll_node_delete(llist_data[1], &free);
	ll_node_delete(llist_data[2], &free);
	ll_node_delete(llist_data[3], &free);
	ll_node_delete(llist_data[4], &free);

	free(l);
}
