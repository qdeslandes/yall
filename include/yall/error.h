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

#ifndef _YALL_ERROR_H
#define _YALL_ERROR_H

#include "yall/utils.h"

// Typedef'd as it should be used by end user.
typedef enum {
	YALL_SUCCESS		= 0x00,
	YALL_UNKNOW_ERROR	= 0x01,

	// TODO : specify error categories
	YALL_ALREADY_INIT	= 0x02,
	YALL_NOT_INIT		= 0x03,
	YALL_SEM_INIT_ERR	= 0x04,
	YALL_NO_MEM		= 0x05,
	YALL_LOG_LEVEL_TOO_LOW	= 0x06,

	YALL_NO_NAME		= 0x07,

	YALL_FILE_LOCK_ERR	= 0x08,
	YALL_FILE_OPEN_ERR	= 0x09,

	YALL_CONSOLE_LOCK_ERR	= 0x0A,
	YALL_CONSOLE_WRITE_ERR	= 0x0B,

	YALL_STRING_WRITE_ERR	= 0x0C,

	YALL_SUBSYS_NOT_EXISTS	= 0x0D,
	YALL_SUBSYS_DISABLED	= 0x0E,

	YALL_CANT_CREATE_SUBSYS	= 0x0F,

	YALL_CANT_CREATE_THREAD	= 0x10,

	/*
	 * This is used to check if the given code is defined. It is ugly, but
	 * it's the best I can currently find.
	 */
	yall_err_end		= 0x11
} yall_error;

_YALL_PUBLIC const char *yall_strerror(yall_error err);

#endif
