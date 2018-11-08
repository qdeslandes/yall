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

#ifndef _TEST_CONTAINER_LLIST_H
#define _TEST_CONTAINER_LLIST_H

#include "container/test.h"
#include "yall/container/llist.h"

struct llist_node_t {
	struct llist_node_t *next;
	struct llist_node_t *previous;
	void *data;
};

struct llist_t {
	struct llist_node_t *head;
	struct llist_node_t *tail;
	uint32_t size;
};

struct test_llist_data {
	int a;
	int b;
	int c;
};

#define CREATE_LLIST_DATA(name, val_a, val_b, val_c) \
	struct test_llist_data *name = malloc(sizeof(struct test_llist_data)); \
	do { \
		name->a = val_a; \
		name->b = val_b; \
		name->c = val_c; \
	} while (0)

#define SET_LLIST_CHAIN(n_previous, n_current, n_next) \
	do { \
		n_previous->next = n_current; \
		n_current->previous = n_previous; \
		n_current->next = n_next; \
		n_next->previous = n_current; \
	} while (0)

extern llist_node_t *llist_data[5];
extern llist_node_t *ll_node_new(void *data);
extern void *ll_node_delete(llist_node_t *n, void (*data_delete)(void *data));
extern llist_node_t *ll_get_node_at(llist_t *l, int32_t index);
extern llist_node_t *ll_remove_node_at(llist_t *l, int32_t index);
extern void ll_insert_node_at(llist_t *l, int32_t index, llist_node_t *n);

void test_llist_data_deleter(void *data);
struct test_llist_data *test_llist_get_fake_data(int a, int b, int c);
llist_t *test_llist_test_data(void);
void test_llist_free_data(llist_t *l);

#endif
