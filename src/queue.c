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
#include <malloc.h>
#include <stdatomic.h>

#ifdef __linux__
#define yall_aligned_alloc(alignment, size) aligned_alloc(alignment, size)
#define yall_aligned_free(ptr) free(ptr)
#elif _WIN32
#include <Windows.h>
#define yall_aligned_alloc(alignment, size) _aligned_malloc(size, alignment)
#define yall_aligned_free(ptr) _aligned_free(ptr)
#endif

#include "yall/message.h"

/*
 * Queue head is not set volatile as it would reduce code speed and not ensure
 * atomicity of operations ;
 * https://software.intel.com/en-us/blogs/2007/11/30/volatile-almost-useless-for-multi-threaded-programming
 */
static struct qnode *head = NULL;

struct qnode *qnode_new(void *data)
{
	struct qnode *node = yall_aligned_alloc(64, sizeof(struct qnode));

	// Ensure <next> is set to NULL, as it is used to check queue's tail.
	node->next = NULL;

	node->data = data;

	return node;
}

void qnode_delete(struct qnode *node, void (*data_delete)(void *data))
{
	if (data_delete)
		data_delete(node->data);
	else
		free(node->data);

	yall_aligned_free(node);
}

void enqueue(void *data)
{
	struct qnode *new_node = qnode_new(data);
	struct qnode *orig_head = head;

	do {
		orig_head = head;
		new_node->next = orig_head;
	} while (! atomic_compare_exchange_weak(&head, &orig_head, new_node));
}

struct qnode *swap_queue(void)
{
	if (! head)
		return NULL;

	struct qnode *orig_head = NULL;

	do {
		orig_head = head;
	} while (! atomic_compare_exchange_weak(&head, &orig_head, NULL));

	return orig_head;
}
