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

#include "yall/container/queue.h"

#include <stdint.h>
#include <stdlib.h>

/**
 * \struct queue_node_t
 * \brief This structure represents a queue node.
 * \var queue_node_t::next
 *	\brief Next node in the queue.
 * \var queue_node_t::previous
 *	\brief Previous node in the queue.
 * \var queue_node_t::data
 *	\brief Data stored in the node.
 */
struct queue_node_t {
	struct queue_node_t *next;
	struct queue_node_t *previous;
	void *data;
};

/**
 * \struct queue_t
 * \brief This structure represents a queue using a double linked-list.
 * \var queue_t::head
 *	\brief First element of the list.
 * \var queue_t::tail
 *	\brief Last element of the list.
 */
struct queue_t {
	queue_node_t *head;
	queue_node_t *tail;
};

/**
 * \brief Create a new node with the given data. 'data' can be anything so this
 *	function won't copy it (as we don't know its size).
 * \param data Pointer to the data to add inside the node. No copy is made. Can
 *	be NULL.
 */
static queue_node_t *q_node_new(void *data)
{
	queue_node_t *n = malloc(sizeof(queue_node_t));

	n->next = NULL;
	n->previous = NULL;
	n->data = data;

	return n;
}

/**
 * \brief Delete the given node. 'data_delete' pointer is used to free the
 *	node's data (in case of a compound type).
 * \param n Node to delete.
 * \param data_delete Pointer to a function used to delete the node's data. If
 *	this parameter is NULL, the function call 'free()' on the data.
 */
static void q_node_delete(queue_node_t *n, void (*data_delete)(void *data))
{
	if (data_delete)
		data_delete(n->data);
	else
		free(n->data);

	free(n);
}

queue_t *q_new(void)
{
	queue_t *q = malloc(sizeof(queue_t));

	q->head = NULL;
	q->tail = NULL;

	return q;
}

void q_delete(queue_t *q, void (*data_delete)(void *data))
{
	queue_node_t *n = q->head;

	while (n) {
		queue_node_t *next = n->next;

		q_node_delete(n, data_delete);

		n = next;
	}

	free(q);
}

void q_enqueue(queue_t *q, void *data)
{
	queue_node_t *n = q_node_new(data);

	n->next = q->head;
	if (q->head)
		q->head->previous = n;
	q->head = n;

	if (! q->tail)
		q->tail = n;
}

void *q_dequeue(queue_t *q)
{
	void *data = NULL;
	queue_node_t *n = q->tail;

	if (! q->tail)
		goto end;

	q->tail = n->previous;
	if (q->tail)
		q->tail->next = NULL;

	if (n == q->head)
		q->head = NULL;

	data = n->data;
	n->data = NULL;
	q_node_delete(n, NULL);

end:
	return data;
}
