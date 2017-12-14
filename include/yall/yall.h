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

#ifndef _YALL_H
#define _YALL_H

#ifdef __cplusplus
#include <sstream>
extern "C" {
#endif

#include <stdint.h>

#include "yall/log.h"
#include "yall/call.h"
#include "yall/error.h"
#include "yall/utils.h"
#include "yall/debug.h"
#include "yall/config.h"
#include "yall/log_level.h"
#include "yall/output_types.h"
#include "yall/subsystem.h"

#define YALL_CALL_BUFF_LEN      1024

/*
 * These functions are defined inside subsystem.c, but due to incompatibility
 *      between <atomic> (C++) and <stdatomic.h> (C), subsystem.h can't be
 *      included here.
 */
_YALL_PUBLIC void yall_disable_subsystem(const char *subsys_name);
_YALL_PUBLIC void yall_enable_subsystem(const char *subsys_name);

/*
 * yall_get_version : returns the library version as a 32bits integer with the
 *      form :
 *      * 16 bits : major
 *      * 8 bits  : minor
 *      * 8 bits  : patch
 */
_YALL_PUBLIC uint32_t yall_get_version(void);

/* yall_get_version_string : returns a formated string containing the library
 *      name, its version, and the developer name.
 */
_YALL_PUBLIC const char *yall_get_version_string(void);

/*
 * yall_init : initialize the yall library. It set up the writers and increment
 *      the <initialized> flag each time called.
 *      Returns a yall error code.
 */
_YALL_PUBLIC yall_error yall_init(void);

/*
 * yall_is_init : returns the number initialization done without closing the
 * 	library.
 */
_YALL_PUBLIC uint16_t yall_is_init(void);

/*
 * yall_log : major logging function, used to forge the message and write it
 *      on the medium. <subsystem>, <function> and <msg> can't be NULL.
 *      Returns a yall error code.
 */
_YALL_PUBLIC yall_error yall_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function,
	const char *filename,
	int32_t line,
	const char *format,
	...);

/*
 * yall_call_log : another logging function which call the given <function>
 *      parameter to change message format. It will get the subsystem's
 *      parameters and use them to add header on the logging message. Then
 *      it will call the given function with a buffer to fill.
 *      The buffer will then be displayed.
 *      The buffer length is defined by YALL_CALL_BUFF_LEN. <subsystem> and
 *      <function> can't be NULL.
 *      Returns a yall error code.
 */
_YALL_PUBLIC yall_error yall_call_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function_name,
	const char *filename,
	int32_t line,
	void (*formatter)(yall_call_data *d, const void *args),
	const void *args);

/*
 * yall_set_subsystem : this is the main subsystems function. This function
 *      handle subsystems creation and update. If <name> is the name of an
 *      existing subsystem, it is updated : removed from the subsystems tree,
 *      updated and replaced in its correct place with correct inheritance. If
 *      <name> is not the name of an existing subsystem, it is created with the
 *      proper parameters and inserted in the subsystems tree at the proper
 *      place.
 *      <name> parameter must be a non NULL, NULL terminated string.
 *      Returns a yall error code.
 */
_YALL_PUBLIC yall_error yall_set_subsystem(const char *name,
	const char *parent,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file);

/*
 * yall_close : close all the yall library set up. The function fail only
 *      if yall has not been initialized previously. If the function succeed,
 *      the <initialized> value is decremented. If <initialized> equals 0 once
 *      decremented, the library is cleaned.
 *      Returns a yall error code.
 */
_YALL_PUBLIC yall_error yall_close(void);

/*
 * yall_close_all : close the yall library for each time it has been
 *      initialized.
 */
_YALL_PUBLIC void yall_close_all(void);

#ifdef __cplusplus
}
#endif

#endif
