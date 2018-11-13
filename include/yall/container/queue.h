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

#ifndef _YALL_CONTAINER_QUEUE_H
#define _YALL_CONTAINER_QUEUE_H

typedef struct queue_t queue_t;
typedef struct queue_node_t queue_node_t;

/*
 * This file stores all the function used to handle queues. This queue can't be
 * used in a multithreaded environment (or an external synchronization
 * mechanism must be used).
 */

#include <yall/utils.h>

/**
 * \brief Create a new queue.
 * \return Pointer to the new queue.
 */
queue_t *q_new(void);

/**
 * \brief Delete the given queue. All data stored inside the queue's nodes will
 *	will be delete either using 'data_delete' function pointer or using
 *	'free()' if 'data_delete' is NULL.
 * \param q Queue pointer, can't be NULL.
 * \param data_delete Pointer to the data deletion function. Can be NULL.
 */
void q_delete(queue_t *q, void (*data_delete)(void *data));

/**
 * \brief Add data to the queue. The data won't be copied, which means it must
 *	not be freed outside the queue until the pointer is used in the queue.
 * \param q Pointer to the queue.
 * \param data Pointer to the data to enqueue.
 */
void q_enqueue(queue_t *q, void *data);

/**
 * \brief Dequeue data from the queue in a FIFO fashion. Returns the pointer to
 *	the data.
 * \param q Pointer to the queue.
 */
void *q_dequeue(queue_t *q);

#endif
