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

#ifndef _YALL_CONTAINER_LLIST_H
#define _YALL_CONTAINER_LLIST_H

#include <stdint.h>

typedef struct llist_node_t llist_node_t;
typedef struct llist_t llist_t;

/**
 * \brief Create a new linked-list object. This object must be used each time
 *	you call a function accessing / modifying the linked-list.
 * \return Pointer to the linked-list object.
 */
llist_t *ll_new(void);

/**
 * \brief Delete the given linked-list. The data present in each node will be
 *	passed to 'data_delete' function pointer. This function can then manage
 *	the data or free it ('data_delete' could be a pointer to stdlib's
 *	'free()'). If 'data_delete' is NULL, nothing will be done to the node's
 *	data (meaning the data won't be freed). This function doesn't use
 *	llist internal parsing function, as we don't need to ensure the list
 *	remain consistent between node's freeing.
 * \param l Pointer to the linked-list object.
 * \param data_delete Pointer to the function managing linked-list node's data.
 */
void ll_delete(llist_t *l, void (*data_delete)(void *data));

/**
 * \brief Insert the data at the given position. If the position does not exists
 *	in the list (insert at index 40 in a list composed of 3 elements, for
 *	example), insert the node at the end of the list.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \param index Index of the new node.
 * \param data Pointer to the data stored inside the node.
 */
void ll_insert_at(llist_t *l, int32_t index, void *data);

/**
 * \brief Insert the data at the beginning of the list.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \param data Pointer to the data stored inside the node.
 */
void ll_insert_first(llist_t *l, void *data);

/**
 * \brief Insert the data at the end of the list.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \param data Pointer to the data stored inside the node.
 */
void ll_insert_last(llist_t *l, void *data);

/**
 * \brief Return a pointer to the data stored in node at 'index'. This function
 *	does not remove the node from the list. If the value of 'index' is
 *	invalid, return the data from the last node of the list.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \param index Index of the node containing the data to return.
 * \return Pointer to the data stored in node at given index.
 */
void *ll_get_at(llist_t *l, int32_t index);

/**
 * \brief Return a pointer to the data stored in first node of the list.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \return Pointer to the data stored in first node.
 */
void *ll_get_first(llist_t *l);

/**
 * \brief Return a pointer to the data stored in last node of the list.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \return Pointer to the data stored in last node.
 */
void *ll_get_last(llist_t *l);

/**
 * \brief Remove the node at 'index'. The node's data is returned. If the value
 *	of 'index' is invalid, return the data from the last node of the list.
 *	Caller must take care of the data as they won't be freed by the
 *	function.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \param index Index of the node to be removed.
 * \return Pointer to the data then stored in the removed node.
 */
void *ll_remove_at(llist_t *l, int32_t index);

/**
 * \brief Remove the first node of the list. Return its data.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \return Pointer to the data then stored in the removed node.
 */
void *ll_remove_first(llist_t *l);

/**
 * \brief Remove the last node of the list. Return its data.
 * \param l Pointer to the linked-list. Can't be NULL.
 * \return Pointer to the data then stored in the removed node.
 */
void *ll_remove_last(llist_t *l);

#endif
