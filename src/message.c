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

#include "yall/message.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yall/utils.h"
#include "yall/errors.h"
#include "yall/subsystem.h"
#include "yall/debug.h"
#include "yall/header.h"

uint8_t generate_message(char *buffer,
	const char *format,
	const struct header_content *hc,
        va_list args)
{
	uint8_t ret = YALL_OK;

        ret = generate_header(buffer, hc);
        if (ret != YALL_OK) {
                goto end;
        }

        size_t len = strlen(buffer);
        if (vsnprintf(&buffer[len], YALL_MSG_LEN - len, format, args) < 0)
                ret = YALL_STRING_WRITE_ERR;

        len = strlen(buffer);
        if (len == YALL_MSG_LEN - 1)
                --len;

        buffer[len] = '\n';
        buffer[len+1] = '\0';

end:
        return ret;
}
