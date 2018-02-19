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

#include "yall/debug.h"

#include <string.h>
#include <stdlib.h>

#include "yall/subsystem.h"

static bool debug = false;
static const char *debug_subsystem = NULL;

yall_error yall_enable_debug(const char *subsystem)
{
	yall_error ret = YALL_SUCCESS;
	struct yall_subsystem *s = NULL;

	if (! yall_is_init())
		return YALL_NOT_INIT;

	s = get_subsystem(subsystem, NULL);
	if (! s)
		return YALL_SUBSYS_NOT_EXISTS;

	/*
	 * The order of the following instructions is critical : first we
	 * define the subsystem, but the debug flag must be set to false.
	 * Otherwise, it will search for the subsystem before creating it,
	 * it will not find it and then try to log a debug message to
	 * inform the user this subsystem is not found, which will lead
	 * to a call to get_subsystem() which will search the subsystem,
	 * but it will not find it, ...
	 */

	/*
	 * TODO : what if the subsystem already exists ? Then the parameters
	 * will be overrided by the following instruction. It could be
	 * interesting to check availability of such subsystem.
	 */

	debug_subsystem = strdup(subsystem);

	debug = true;

	_YALL_DBG_DEBUG("Debug mode activated.");

	return ret;
}

yall_error yall_disable_debug(void)
{
	yall_error ret = YALL_SUCCESS;

	if (! yall_is_init())
		return YALL_NOT_INIT;

	_YALL_DBG_DEBUG("Debug mode disactivated.");

	debug = false;
	free((char *)debug_subsystem);
	debug_subsystem = NULL;

	return ret;
}

bool yall_is_debug(void)
{
	return debug;
}

const char *debug_subsystem_name(void)
{
	return debug_subsystem;
}
