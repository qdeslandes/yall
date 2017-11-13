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

#ifndef _WRITER_H
#define _WRITER_H

#include <stdint.h>

#include "yall/output_types.h"
#include "yall/log_level.h"
#include "yall/error.h"

/*
 * writer_init : initialize some stuff for the console and file writers.
 *      Currently initialize the semaphores. This should be called once.
 *      TODO : Manage to fail the initialization if the semaphore are already
 *      initialized.
 *	Returns a yall_error.
 */
yall_error writer_init(void);

/*
 * write : write the message to the output medium. Returns a YALL_ERROR on
 *      error. <msg> must not be NULL, but <output_file> can if <output_type>
 *      is equals to yall_file_output or yall_both_output.
 *	Returns a yall_error.
 */
yall_error write_msg(enum yall_output_type output_type,
	enum yall_log_level log_level,
	const char *output_file,
	const char *msg);

/*
 * writer_destroy : destroy all the writers semaphores.
 */
void writer_close(void);

#endif
