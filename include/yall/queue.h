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

#ifndef _YALL_QUEUE_H
#define _YALL_QUEUE_H

/*
 * This file contain the queue function's prototype. Orignally, this queue was
 * used to store the log message, while the writer thread was writing them.
 * It should be lock free to avoid race conditions inside the library. The lock
 * free property is not hard to implement, as this is not a real queue : the
 * logger thread add data to the queue, in a stack way : head become head->next
 * and the new node become the head. The writer thread copy the head pointer and
 * replace the head value to NULL, which lead to the creation of a "new" queue.
 */

/*
 * struct qnode : represent a queue node. The <next> pointer is supposed to be
 *	volatile as is should not be optimized too much by the compiler.
 */
struct qnode {
	struct qnode *next;
	void *data;
};

/*
 * qnode_new : create a new node with the given data. On windows, the
 *	implementation use an aligned version of malloc to get a memory
 *	pointer. <next> pointer of the node *MUST* be set to NULL, as it is
 *	used to check the queue's tail.
 */
struct qnode *qnode_new(void *data);

/*
 * qnode_delete : delete the given queue node. <data_delete> is a function
 *	pointer (void funct(void *data)) use to delete the node data in a
 *	custom way. On windows, it use aligned_free to complete with
 *	aligned_malloc on qnode_new(). If NULL is given, qnode_delete will
 *	call free() on the data.
 */
void qnode_delete(struct qnode *node, void (*data_delete)(void *data));

/*
 * enqueue : create a node with the given data and add it to the queue.
 */
void enqueue(void *data);

/*
 * swap_queue : as the writer thread get the whole queue when writing, there is
 *	no dequeue() function (currently), but a function to return the
 *	current's queue head, and the set head to NULL. If the queue is empty,
 *	NULL is returned.
 */
struct qnode *swap_queue(void);

#endif
