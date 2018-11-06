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

#ifndef _YALL_WRITER_H
#define _YALL_WRITER_H

#include <stdint.h>

#include "yall/output/types.h"
#include "yall/log_level.h"
#include "yall/message.h"
#include "yall/error.h"

/**
 * \brief Start the writing thread. Also, this function does create a cqueue_t
 *	object and send it to the thread. This object is used to share the
 *	messages to write between the threads and the writing thread.
 * \param frequency Frequency to use for the writer's thread loops.
 * \return Error code depending of the success or failure of the function.
 */
yall_error writer_init(uint16_t frequency);

/**
 * \brief Enqueue the given message to the lock-free queue.
 * \return Error code depending of the success or failure of the function.
 */
void write_msg(struct message *m);

/**
 * \brief Stop the writing thread. Delete messages queue which should be empty.
 */
void writer_close(void);

#endif
