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

#include "yall/subsystem.h"

static bool debug = false;

void yall_enable_debug(void)
{
#ifdef DEBUG
	if (! yall_is_init())
		return;

	/*
	 * The order of the following instructions is critical : first we
	 * define the subsystem, but the debug flag must be set to false.
	 * Otherwise, it will search for the subsystem before creating it,
	 * it will not find it and then try to log a debug message to
	 * inform the user this subsystem is not found, which will lead
	 * to a call to get_subsystem() which will search the subsystem,
	 * but it will not find it, ...
	 */

	yall_set_subsystem("yall", NULL, yall_debug, yall_console_output, NULL);

	debug = true;

	_YALL_DBG_DEBUG("Debug mode activated.");
#endif
}

void yall_disable_debug(void)
{
#ifdef DEBUG
	if (! yall_is_init())
		return;

	_YALL_DBG_DEBUG("Debug mode disactivated.");

	debug = false;
	_free_subsystems(remove_subsystem("yall"));
#endif
}

bool yall_is_debug(void)
{
	return debug;
}
