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

typedef struct cqueue_node_t cqueue_node_t;
typedef struct cqueue_t cqueue_t;

struct cqueue_node_t {
    cqueue_node_t *next;
    void *data;
};

struct cqueue_t{
    cqueue_node_t *nodes;
};

cqueue_node_t *cq_node_new(void *data)
{
    cqueue_node_t *n = malloc(sizeof(cqueue_node_t));

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

    free(n);
}

cqueue_t *cq_new(void)
{
    cqueue_t *q = malloc(sizeof(cqueue_t));

    q->nodes = NULL;

    return q;
}

// NON concurrent
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
        free(n);
    }

end:
    return data;
}
