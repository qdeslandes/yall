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
 *	data (meaning the data won't be freed).
 * \param l Pointer to the linked-list object.
 * \param data_delete Pointer to the function managing linked-list node's data.
 */
void ll_delete(llist_t *l, void (*data_delete)(void *data));

void ll_insert_at(llist_t *l, int32_t index, void *data);
void ll_insert_first(llist_t *l, void *data);
void ll_insert_last(llist_t *l, void *data);

void *ll_get_at(llist_t *l, int32_t index);
void *ll_get_first(llist_t *l);
void *ll_get_last(llist_t *l);

void *ll_remove_at(llist_t *l, int32_t index);
void *ll_remove_first(llist_t *l);
void *ll_remove_last(llist_t *l);

#endif
