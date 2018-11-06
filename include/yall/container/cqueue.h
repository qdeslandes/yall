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

#ifndef _YALL_CONTAINER_CQUEUE_H
#define _YALL_CONTAINER_CQUEUE_H

typedef struct cqueue_node_t cqueue_node_t;

/**
 * \struct cqueue_t
 * \brief This structure represents a concurrent queue.
 * \var cqueue_t::nodes
 *	\brief Singly linked-list of queue nodes.
 */
typedef struct cqueue_t {
	cqueue_node_t *nodes;
} cqueue_t;

/*
 * This file store all the function to create and use concurrent queues. This
 * means this kind of queue can be modified in a multithread environment. Thus,
 * enqueing, dequeing and queue swapping is thread safe.
 * This structure use a single-linked-list in order to easily add / remove
 * nodes. It means that, in order to dequeue in the proper order, you have to
 * call 'cq_swap()', this function aims to define a new cqueue_t object storing
 * the previous queue in the proper order. Thus, you can't dequeue from a
 * cqueue_t you have enqueued without calling 'cq_swap()' before.
 * 
 * The typical workflow to use with this concurrent queue is:
 * 	- cq_enqueue() to add elements
 *	- cq_swap() to get all queue's elements, allowing to insert new ones
 *	- cq_dequeue() to get node's elements
 *
 * Concurrent queue mechanism implemented here does take ownership of the data
 * present in the nodes. The only way to take back data ownership is through
 * dequeueing. Otherwise, the queue does handle all the life of the node's data.
 */

/**
 * \brief Create a new concurrent queue.
 * \return Pointer to the concurrent queue. Must be freed calling 'cq_delete()'.
 */
cqueue_t *cq_new(void);

/**
 * \brief Delete the given concurrent queue. Each element of the queue will
 *	be freed too. The node's content will be deleted using 'data_delete'
 *	function, or 'free()' if 'data_delete' is NULL.
 * \param q Pointer to the queue to delete. Can't be NULL.
 * \param data_delete Function to call in order to free the node's data or NULL.
 */
void cq_delete(cqueue_t *q, void (*data_delete)(void *data));

/**
 * \brief Add data to the given queue. 'data' will be added in a new queue node,
 *	and this queue node will be inserted as first element of the queue.
 *	This function is thread-safe.
 * \param q Pointer to the queue. Can't be NULL.
 * \param data Pointer to the data to add to the given queue. Can be NULL.
 */
void cq_enqueue(cqueue_t *q, void *data);

/**
 * \brief Dequeue the last node of the given queue and return the data. The node
 *	is deleted.
 *	This function is thread-safe.
 * \param q Queue to remove a node from. Can't be NULL.
 * \return Pointer to the removed node's data. Can be NULL.
 */
void *cq_dequeue(cqueue_t *q);

/**
 * \brief Swap the given queue. Nodes from 'from' queue will be set as node from
 *	'to' queue. 'to' queue will then be reversed, meaning the user, once
 *	'cq_swap' called, can call 'cq_dequeue()' on 'to' queue. 'from' queue
 *	is then empty.
 *	This function is thread safe.
 * \param from Queue to swap. After function completion, node list of this queue
 *	will be empty. Can't be NULL.
 * \param to Queue containing the reversed node once function completes.
 * \return Swapped queue. This queue has to be freed by the user once done.
 *	Can't be NULL.
 */
void cq_swap(cqueue_t *from, cqueue_t *to);

#endif
