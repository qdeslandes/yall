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
#include "yall/config/parameters.h"
#include "yall/log_level.h"
#include "yall/output_types.h"
#include "yall/subsystem.h"
#include "yall/config/reader.h"

/*
 * These functions are defined inside subsystem.c, but due to incompatibility
 *      between <atomic> (C++) and <stdatomic.h> (C), subsystem.h can't be
 *      included here.
 */
_YALL_PUBLIC void yall_disable_subsystem(const char *subsys_name);
_YALL_PUBLIC void yall_enable_subsystem(const char *subsys_name);

/**
 * \brief Returns the library version as a 32bits integer with the form :
 *	* 16 bits : major
 *	* 8 bits  : minor
 *	* 8 bits  : patch
 * \return Current version of the library.
 */
_YALL_PUBLIC uint32_t yall_get_version(void);

/**
 * \brief Returns a formatted string containing the library name, its version,
 *	and the developer name.
 * \return Formatted string of the library version.
 */
_YALL_PUBLIC const char *yall_get_version_string(void);

/**
 * \brief Initialize the yall library. It set up the writers and increment the
 *	initialized counter.
 *	This function must be called prior to anyone else. It the initialization
 *	fails, the library can't be used.
 * \return Error code whether it has been initialized.
 */
_YALL_PUBLIC yall_error yall_init(void);

/**
 * \brief Returns the number initialization done without closing the
 *	library.
 * \return The value of the initializations counter.
 */
_YALL_PUBLIC uint16_t yall_is_init(void);

/**
 * \brief Load the configuration stored in the parameter. This configuration
 *	file can store a list of configuration parameters and a list of
 *	subsystems to define.
 * \param filepath Path to the configuration file.
 * \return Error code whether the configuration has been loaded.
 */
_YALL_PUBLIC yall_error yall_load_configuration(const char *filepath);

/**
 * \brief Major logging function, used to forge the message and write it on the
 *	medium. Given the parameters, it will decide if the message should be
 *	logged or not. This function should not be used as it but through all
 *	the macro (YALL_DEBUG(), ...).
 * \param subsystem Name of the subsystem as a nul-terminated string. Can't be
 *	NULL.
 * \param log_level Log level to use for this log message.
 * \param function Name of the calling function, defaultly used in the log
 *	message's header. Can't be NULL.
 * \param filename Name of the file calling the log function.
 * \param line Line on which this function has been called.
 * \param format Format of the log message, in a printf() way. Can't be NULL.
 * \param ... Variadic parameters to use with the described defined format. All
 *	the printf() like functions modifiers can be used.
 * \return Error code depending of the success or failure of the function.
 */
_YALL_PUBLIC yall_error yall_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function,
	const char *filename,
	int32_t line,
	const char *format,
	...);

/**
 * \brief Another logging function which call the given *function*
 *	parameter to change message format. It will get the subsystem's
 *	parameters and use them to add header on the logging message. Then
 *	it will call the given function with a buffer to fill.
 * \param subsystem Name of the calling function, defaultly used in the log
 *	message's header. Can't be NULL.
 * \param log_level Log level to use for this log message.
 * \param function_name Name of the calling function, defaultly used in the log
 *	message's header. Can't be NULL.
 * \param filename Name of the file calling the log function.
 * \param line Line on which this function has been called.
 * \param formatter Function which will handle the logging of the message. The
 *	given *d* parameter of type yall_call_data will contain of the necessary
 *	data for yall to process the log message. Inside this formatting
 *	function yall_call_set_header() and yall_call_add_line() can be called.
 * \param args void * pointer to custom arguments to passe to the formatter
 *	function.
 * \return Error code depending of the success or failure of the function.
 */
_YALL_PUBLIC yall_error yall_call_log(const char *subsystem,
	enum yall_log_level log_level,
	const char *function_name,
	const char *filename,
	int32_t line,
	void (*formatter)(yall_call_data *d, const void *args),
	const void *args);

/**
 * \brief This is the main subsystems function. This function handle subsystems
 *	creation and update.
 *	If *name* is the name of an existing subsystem, it is updated : removed
 *	from the subsystems tree, updated and replaced in its correct position
 *	with correct inheritance.
 *	If *name* is not the name of an existing subsystem, it is created with
 *	the proper parameters and inserted in the subsystems tree at the proper
 *	place.
 * \param name Name of the subsystem to add or update. Can't be NULL.
 * \param parent Name of the parent to inherit from. If NULL, this subsystem
 *	will be at top-level of the tree.
 * \param log_level Minimum log level to use for this subsystem. All the log
 *	messages with a log level below this one will be discarded.
 * \param output_type Default output type for this subsystem.
 *	See yall_output_type.
 * \param output_file File to use of the subsystem's default output type is
 *	yall_file_output.
 * \return Error code depending of the success or failure of the function.
 */
_YALL_PUBLIC yall_error yall_set_subsystem(const char *name,
	const char *parent,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file);

/**
 * \brief Close all the yall library set up. The function fail only if yall has
 *	not been previously initialized. If the function succeed, the
 *	initialization counter's value is decremented. If *initialized* equals
 *	0 once decremented, the library is cleaned.
 * \return Error code depending of the success or failure of the function.
 */
_YALL_PUBLIC yall_error yall_close(void);

/**
 * \brief Close the yall library for each time it has been initialized. After
 *	this function has been used, you can't use the library anymore until
 *	it has been initialized.
 */
_YALL_PUBLIC void yall_close_all(void);

#ifdef __cplusplus
}
#endif

#endif
