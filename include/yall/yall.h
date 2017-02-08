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

#ifndef _YALL_H
#define _YALL_H

#ifdef __cplusplus
#include <sstream>
extern "C" {
#endif

#include <stdint.h>

#include "yall/log.h"
#include "yall/utils.h"
#include "yall/log_levels.h"
#include "yall/output_types.h"

#define YALL_CALL_BUFF_LEN	1024

/*
 * yall_init : initialize the yall library. It set up the writers and the
 * 	<initialized> flag.
 * 	Returns a yall error code.
 */
_YALL_PUBLIC uint8_t yall_init(void);

/*
 * yall_log : major logging function, used to forge the message and write it
 * 	on the medium. <subsystem>, <function> and <msg> can't be NULL.
 * 	Returns a yall error code.
 */
_YALL_PUBLIC uint8_t yall_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function,
	const char *format,
	...);

/*
 * yall_call_log : another logging function which call the given <function>
 * 	parameter to change message format. It will get the subsystem's
 * 	parameters and use them to add header on the logging message. Then
 * 	it will call the given function with a buffer to fill.
 * 	The buffer will then be displayed.
 * 	The buffer length is defined by YALL_CALL_BUFF_LEN. <subsystem> and
 * 	<function> can't be NULL.
 */
_YALL_PUBLIC uint8_t yall_call_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function_name,
	void (*function)(char *buffer, void *args),
	void *args);

/*
 * yall_set_subsystem : this is the main subsystems function. This function
 *	handle subsystems creation and update. If <name> is the name of an
 *	existing subsystem, it is updated : removed from the subsystems tree,
 *	updated and replaced in its correct place with correct inheritance. If
 *	<name> is not the name of an existing subsystem, it is created with the
 *	proper parameters and inserted in the subsystems tree at the proper
 *	place.
 * 	<name> parameter must be a non NULL, NULL terminated string.
 */
_YALL_PUBLIC uint8_t yall_set_subsystem(const char *name,
	const char *parent,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file);

/*
 * yall_close : close all the yall library set up. The function fail only
 *	if yall has not been initialized previously.
 *	Returns a yall error code.
 */
_YALL_PUBLIC uint8_t yall_close(void);

#ifdef __cplusplus
}
#endif

#endif
