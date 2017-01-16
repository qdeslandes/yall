/*
 * Copyright (C) 2017, by Quentin Deslandes
 *
 * This file is part of yall.
 *
 * yall is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * yall is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with yall.  If not, see <http://www.gnu.org/licenses/>.
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
