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
typedef struct cqueue_t cqueue_t;

/*
 * This file store all the function to create and use concurrent queues. This
 * means this kind of queue can be modified in a multithread environment. Thus,
 * enqueing, dequeing and queue swapping is thread safe.
 * This structure use a single-linked-list in order to easily add / remove
 * nodes. It means dequeueing from a queue does not returns the first inserted
 * node, you have to call 'cq_reverse()' on it before.
 * 
 * The typical workflow to use with this concurrent queue is:
 * 	- cq_enqueue() to add elements
 *	- cq_swap() to get all queue's elements, allowing to insert new ones
 *	- cq_reverse() to reverse the old queue
 *	- cq_dequeue() to get node's elements
 */

/**
 * \brief Create a new node with the given data. 'data' can be anything,
 *	thus the function won't copy it, so it musn't be freed outside.
 * \param data Pointer to the data contained by the node.
 * \return Pointer to the new node.
 */
cqueue_node_t *cq_node_new(void *data);

/**
 * \brief Delete the given node. 'data_delete' is a pointer to a
 *	function which can be called to delete the node's data. If 'data_delete'
 *	is NULL, a simple 'free()' is called.
 * \param n Node to delete.
 * \param data_delete Function to call in order to free the node's data or NULL.
 */
void cq_node_delete(cqueue_node_t *n, void (*data_delete)(void *data));

/**
 * \brief Create a new concurrent queue.
 * \return Pointer to the concurrent queue. Must be freed calling 'cq_delete()'.
 */
cqueue_t *cq_new(void);

/**
 * \brief Delete the given concurrent queue. Each element of the queue will
 *	be freed too. The node's content will be deleted using 'data_delete'
 *	function, or 'free()' if 'data_delete' is NULL.
 * \param q Pointer to the queue to delete.
 * \param data_delete Function to call in order to free the node's data or NULL.
 */
void cq_delete(cqueue_t *q, void (*data_delete)(void *data));

/**
 * \brief Add data to the given queue. 'data' will be added in a new queue node,
 *	and this queue node will be inserted as first element of the queue.
 *	This function is thread-safe.
 * \param q Pointer to the queue
 * \param data Pointer to the data to add to the given queue.
 */
void cq_enqueue(cqueue_t *q, void *data);

/**
 * \brief Dequeue the last node of the given queue and return the data. The node
 *	is deleted.
 *	This function is thread-safe.
 * \param q Queue to remove a node from.
 * \return Pointer to the removed node's data.
 */
void *cq_dequeue(cqueue_t *q);

/**
 * \brief Swap the given queue. Return a new queue containing the swapped nodes
 *	list. The original queue is now empty.
 *	This function is thread safe.
 * \param q Queue to swap. After function completion, node list of this queue
 *	will be empty.
 * \return Swapped queue. This queue has to be freed by the user once done.
 */
cqueue_t *cq_swap(cqueue_t *q);

/**
 * \brief Reverse the given queue. Once done, the head of the queue is now the
 *	tail...
 * \param q Queue to reverse.
 */
void cq_reverse(struct cqueue_t *q);

#endif
