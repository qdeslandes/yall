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

#ifndef _YALL_WRITER_FILE_H
#define _YALL_WRITER_FILE_H

#include <stdint.h>

#include "yall/error.h"

/**
 * \brief Write the message to the given log file.
 * \remark Currently, log file opened on each log, we should avoid this
 *	behaviour and keep track of file descriptors.
 * \param file Nul-terminated string represent the path to the log file to write
 *	in.
 * \param msg Final log message to write in the file.
 * \return Error code depending of the success or failure of the function.
 */
yall_error write_log_file(const char *file, const char *msg);

/**
 * \brief Used to remove an old log file from the system.
 * \param filepath Path to the file to delete.
 */
void delete_old_log_file(const char *filepath);

#endif
