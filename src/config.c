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

#include "yall/config.h"

#include <stdlib.h>
#include <string.h>

#include "yall/debug.h"
#include "yall/header.h"

// TODO : set C++ wrapper for these functions

static const struct yall_config default_config = {
	.header_format = "%-16.16s ::: %-9l :: %-17.17f :: %d : ",
	.tab_width = 4
};

static struct yall_config current_config = {
	.header_format = NULL,
	.tab_width = 0
};

void config_setup(void)
{
	yall_config_reset_header_format();
	yall_config_reset_tab_width();
}

void yall_config_set_header_format(const char *format)
{
	free((void *)current_config.header_format);

	current_config.header_format = strdup(format);
	header_compile_format(current_config.header_format);
}

void yall_config_reset_header_format(void)
{
	yall_config_set_header_format(default_config.header_format);
}

const char *yall_config_get_header_format(void)
{
	return current_config.header_format;
}

void yall_config_set_tab_width(uint8_t tab_width)
{
	current_config.tab_width = tab_width;
}

void yall_config_reset_tab_width(void)
{
	yall_config_set_tab_width(default_config.tab_width);
}

uint8_t yall_config_get_tab_width(void)
{
	return current_config.tab_width;
}