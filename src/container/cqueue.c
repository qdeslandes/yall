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

#include "yall/container/cqueue.h"

#include <stdlib.h>

#ifdef __linux__
#include <stdatomic.h>
#define yall_aligned_alloc(alignment, size) aligned_alloc(alignment, size)
#define yall_aligned_free(ptr) free(ptr)
#elif _WIN32
#include <Windows.h>
#define yall_aligned_alloc(alignment, size) _aligned_malloc(size, alignment)
#define yall_aligned_free(ptr) _aligned_free(ptr)
#endif

struct cqueue_node_t {
	cqueue_node_t *next;
	void *data;
};

struct cqueue_t {
	cqueue_node_t *nodes;
};

cqueue_node_t *cq_node_new(void *data)
{
	cqueue_node_t *n = yall_aligned_alloc(64, sizeof(cqueue_node_t));

	n->next = NULL;
	n->data = data;

	return n;
}

void cq_node_delete(cqueue_node_t *n, void (*data_delete)(void *data))
{
	if (data_delete)
		data_delete(n->data);
	else
		free(n->data);

	yall_aligned_free(n);
}

cqueue_t *cq_new(void)
{
	cqueue_t *q = malloc(sizeof(cqueue_t));

	q->nodes = NULL;

	return q;
}

void cq_delete(cqueue_t *q, void (*data_delete)(void *data))
{
	cqueue_node_t *n = q->nodes;

	while (n) {
		cqueue_node_t *next = n->next;

		cq_node_delete(n, data_delete);

		n = next;
	}

	free(q);
}

void cq_enqueue(cqueue_t *q, void *data)
{
	cqueue_node_t *n = cq_node_new(data);
	cqueue_node_t *head = NULL;

	do {
		head = q->nodes;
		n->next = head;
#ifdef __linux__
	} while (! atomic_compare_exchange_weak(&q->nodes, &head, n));
#else
	} while (orig_head !=
		InterlockedCompareExchangePointer(&q->nodes, n, head));
#endif
}

void *cq_dequeue(cqueue_t *q)
{
	void *data = NULL;
	cqueue_node_t *n = q->nodes;

	if (! q->nodes)
		goto end;

	do {
		n = q->nodes;
#ifdef __linux__
	} while (! atomic_compare_exchange_weak(&q->nodes, &n, n->next));
#else
	} while (orig_head !=
		InterlockedCompareExchangePointer(&q->nodes, n->next, n));
#endif

	if (n) {
		data = n->data;

		n->data = NULL;
		cq_node_delete(n, NULL);
	}

end:
	return data;
}

cqueue_t *cq_swap(cqueue_t *q)
{
	cqueue_t *new_q = NULL;
	cqueue_node_t *head = NULL;

	if (! q->nodes)
		goto end;

	do {
		head = q->nodes;
#ifdef __linux__
	} while (! atomic_compare_exchange_weak(&q->nodes, &head, NULL));
#else
	} while (orig_head !=
		InterlockedCompareExchangePointer(&q->nodes, NULL, head));
#endif

	new_q = cq_new();
	new_q->nodes = head;

end:
	return new_q;
}

void cq_reverse(struct cqueue_t *q)
{
	cqueue_node_t *head = q->nodes;
	cqueue_node_t *base = NULL;
	cqueue_node_t *next = NULL;

	while (head) {
		next = head->next;
		head->next = NULL;

		if (! base) {
			base = head;
		} else {
			head->next = base;
			base = head;
		}

		head = next;
	}

	q->nodes = base;
}
