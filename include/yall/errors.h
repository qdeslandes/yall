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

#ifndef _ERRORS_H
#define _ERRORS_H

#define YALL_OK			0x00

#define YALL_ALREADY_INIT	0x10
#define YALL_NOT_INIT		0x11
#define YALL_SEM_INIT_ERR	0x12
#define YALL_NO_MEM		0x13
#define YALL_LOG_LEVEL_TOO_LOW	0x14

#define YALL_NO_NAME		0x20

#define YALL_FILE_LOCK_ERR	0x30
#define YALL_FILE_OPEN_ERR	0x31

#define YALL_CONSOLE_LOCK_ERR	0x40
#define YALL_CONSOLE_WRITE_ERR	0x41

#define YALL_STRING_WRITE_ERR	0x50

#define YALL_SUBSYS_NOT_EXISTS	0x60

#endif
