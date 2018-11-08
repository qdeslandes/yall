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

#include "yall/container/llist.h"

#include <stdlib.h>

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

/**
 * \brief Create a new linked-list node containing the given data. 'data' can
 *	be anything (even NULL). No copy of 'data' is made, if the pointer is
 *	freed somewhere, the one used here will be invalid too.
 * \param data Pointer to the data stored in the new linked-list node.
 * \return Pointer to the linked-list node.
 */
static llist_node_t *ll_node_new(void *data)
{
	llist_node_t *n = malloc(sizeof(llist_node_t));

	n->next = NULL;
	n->previous = NULL;
	n->data = data;

	return n;
}

/**
 * \brief Delete the given node. 'data_delete' function pointer is used to free
 *	the node's data. If the pointer is not NULL, the node's data will be
 *	given as parameter when calling 'data_delete' to manage / free the data.
 *	'data_delete' can be any function, including a pointer to stdlib's
 *	'free()'. If 'data_delete' is NULL, the data is not freed and the data
 *	pointer is returned by the end of the function call (otherwise NULL is
 *	returned).
 * \param n Pointer to the node to delete. The pointer *must* be valid.
 * \param data_delete Pointer to the function in charge to free the node data.
 *	Can be NULL.
 * \return Pointer to the data (if not freed), NULL otherwise.
 */
static void *ll_node_delete(llist_node_t *n, void (*data_delete)(void *data))
{
	void *data = n->data;

	if (data_delete) {
		data_delete(n->data);
		data = NULL;
	}
	
	free(n);

	return data;
}

static llist_node_t *ll_get_node_at(llist_t *l, int32_t index)
{
	llist_node_t *n = NULL;

	// List is empty
	if (! l->size)
		goto end;
	
	// We want the last element
	if (-1 == index || (uint32_t)index >= l->size)
		return l->tail;
	
	// We want an element inside the list
	n = l->head;
	for (int32_t i = 0; i < index; ++i)
		n = n->next;

end:
	return n;
}

static llist_node_t *ll_remove_node_at(llist_t *l, int32_t index)
{
	llist_node_t *n = ll_get_node_at(l, index);

	if (! n)
		goto end;

	if (l->head == n) {
		l->head = n->next;
		if (l->head)
			l->head->previous = NULL;
	}
	
	if (l->tail == n) {
		l->tail = n->previous;
		if (l->tail)
			l->tail->next = NULL;
	}
	
	if (n->previous)
		n->previous->next = n->next;
	
	if (n->next)
		n->next->previous = n->previous;

end:
	return n;
}

static void ll_insert_node_at(llist_t *l, int32_t index, llist_node_t *n)
{

}

llist_t *ll_new(void)
{
	llist_t *l = malloc(sizeof(llist_t));

	l->head = NULL;
	l->tail = NULL;
	l->size = 0;

	return l;
}

void ll_delete(llist_t *l, void (*data_delete)(void *data))
{
	// TODOllist
}

void ll_insert_at(llist_t *l, int32_t index, void *data)
{
	// TODOllist
	/*
	llist_node_t *n = ll_node_new(data);

	if (index > l->count)*/

}

void ll_insert_first(llist_t *l, void *data)
{
	ll_insert_at(l, 0, data);
}

void ll_insert_last(llist_t *l, void *data)
{
	ll_insert_at(l, -1, data);
}

void *ll_get_at(llist_t *l, int32_t index)
{
	// TODOllist
	return NULL;
}

void *ll_get_first(llist_t *l)
{
	return ll_get_at(l, 0);
}

void *ll_get_last(llist_t *l)
{
	return ll_get_at(l, -1);
}

void *ll_remove_at(llist_t *l, int32_t index)
{
	void *data = NULL;
	llist_node_t *n = ll_get_node_at(l, index);

	if (! n)
	// TODOllist
	return NULL;
}

void *ll_remove_first(llist_t *l)
{
	return ll_remove_at(l, 0);
}

void *ll_remove_last(llist_t *l)
{
	return ll_remove_at(l, -1);
}
