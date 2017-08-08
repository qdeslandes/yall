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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/queue.h"

#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>

#include "yall/message.h"

static volatile struct qnode *head = NULL;

volatile struct qnode *qnode_new(void *data)
{
	volatile struct qnode *node = _aligned_malloc(sizeof(struct qnode), 64);

	// Ensure <next> is set to NULL, as it is used to check queue's tail.
	node->next = NULL;

	node->data = data;

	return node;
}

void qnode_delete(volatile struct qnode *node, void (*data_delete)(void *data))
{
	if (data_delete)
		data_delete(node->data);
	else
		free(node->data);

	_aligned_free((struct qnode *)node);
}

void enqueue(void *data)
{
	volatile struct qnode *new_node = qnode_new(data);
	volatile struct qnode *orig_head = head;

	do {
		orig_head = head;
		new_node->next = orig_head;
	} while (orig_head != InterlockedCompareExchangePointer(&head, new_node, orig_head));
}

volatile struct qnode *swap_queue(void)
{
	if (! head)
		return NULL;

	volatile struct qnode *orig_head = NULL;

	do {
		orig_head = head;
	} while (orig_head != InterlockedCompareExchangePointer(&head, NULL, orig_head));

	return orig_head;
}