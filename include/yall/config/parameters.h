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

#ifndef _YALL_CONFIG_PARAMETERS_H
#define _YALL_CONFIG_PARAMETERS_H

#include <stdint.h>

#include "yall/utils.h"

/*
 * All these function handle the library parameters. No description is required
 * for most of them, as they are short and the name describe itself.
 * The current available parameters are :
 *	* Define the messages header
 *	* Define the call messages header
 *	* Define the indentation size for call messages log
 *
 * All these parameters can be set, reset or get'ed.
 */

/**
 * \struct yall_config
 * \brief This structure store the current configuration of the library. Each
 *	configuration parameter we had should be added to this structure.
 * \var yall_config::std_header_template
 *	\brief Header (beginning of the log message with subsystem name,
 *	function name, ...) when calling YALL_xxx macros.
 * \var yall_config::call_header_template
 *	\brief Header (beginning of the log message with subsystem name,
 *	function name, ...) used when calling YALL_CALL_xxx macros.
 * \var yall_config::tab_width
 *	\brief Width used when indenting log message on YALL_CALL_xxx macros.
 */
struct yall_config {
	const char *std_header_template;
	const char *call_header_template;
	uint8_t tab_width;
};

/**
 * \brief Set library configuration to the default values.
 */
void config_setup(void);

/**
 * \brief Clean allocated memory for the current configuration.
 */
void config_clean(void);

/**
 * \brief Set standard header template of the library.
 * \param std_header_template Format of the standard header template to use.
 *	This format can contain all printf() modifier and all yall modifier
 *	available in is_modifier().
 */
_YALL_PUBLIC void yall_config_set_std_header_template(
	const char *std_header_template);

/**
 * \brief Reset standard header template to default values.
 */
_YALL_PUBLIC void yall_config_reset_std_header_template(void);

/**
 * \brief Returns the current standard header template format.
 * \return Current standard header template format as a nul-terminated string.
 */
_YALL_PUBLIC const char *yall_config_get_std_header_template(void);

/**
 * \brief Set call header template of the library.
 * \param call_header_template Format of the call header template to use. This
 *	format can contain all printf() modifier and all yall modifier available
 *	in is_modifier().
 */
_YALL_PUBLIC void yall_config_set_call_header_template(
	const char *call_header_template);

/**
 * \brief Reset call header template to default values.
 */
_YALL_PUBLIC void yall_config_reset_call_header_template(void);

/**
 * \brief Returns the current call header template format.
 * \return Current call header template format as a nul-terminated string.
 */
_YALL_PUBLIC const char *yall_config_get_call_header_template(void);

/**
 * \brief Set the call logs indent with.
 * \param tab_width Width to use (in characters) when indenting call logs.
 */
_YALL_PUBLIC void yall_config_set_tab_width(uint8_t tab_width);

/**
 * \brief Reset tabulation width to default values.
 */
_YALL_PUBLIC void yall_config_reset_tab_width(void);

/**
 * \brief Returns the current tabulation width value.
 * \return Current tabulation width value.
 */
_YALL_PUBLIC uint8_t yall_config_get_tab_width(void);

#endif
