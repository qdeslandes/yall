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

#ifndef _TEST_CONTAINER_CQUEUE_H
#define _TEST_CONTAINER_CQUEUE_H

#include "container/test.h"
#include "yall/container/cqueue.h"

#define CREATE_NODE(name, val0, val1, val2) \
	struct test_cqueue_node_data *name = NULL; \
	do { \
		name = malloc(sizeof(struct test_cqueue_node_data)); \
		name->a = val0; \
		name->b = val1; \
		name->c = val2; \
	} while (0)

struct test_cqueue_node_data {
	int a;
	int b;
	int c;
};

extern struct test_cqueue_node_data *nodes[3];
extern cqueue_node_t *cq_node_new(void *data);
extern void cq_reverse(cqueue_t *q);
extern void cq_node_delete(cqueue_node_t *n, void (*data_delete)(void *data));

void test_cqueue_node_data_deleter(void *data);
cqueue_t *test_cqueue_empty_queue(void);
cqueue_t *test_cqueue_queue(void);

#endif
