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

#ifndef _YALL_CONFIG_H
#define _YALL_CONFIG_H

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

struct yall_config { /// \struct yall_config
	const char *std_header_template;
	const char *call_header_template;
	uint8_t tab_width;
};

/**
 * \brief Used to initialize the configuration system, it setup default values
 * 	to the different yall parameters.
 */
void config_setup(void);

/**
 * \brief Clean the allocated memory by the current configuration.
 */
void config_clean(void);

/**
 * \brief Setter for standard header template. The standard header is the text
 * 	displayed before the standard log line.
 * \param std_header_template Format of the header used. Can't be NULL.
 */
_YALL_PUBLIC void yall_config_set_std_header_template(
	const char *std_header_template);

/**
 * \brief Reset the standard header template to the default value.
 */
_YALL_PUBLIC void yall_config_reset_std_header_template(void);

/**
 * \brief Returns the format of the standard header currently used.
 * \return Current standard header format.
 */
_YALL_PUBLIC const char *yall_config_get_std_header_template(void);

/**
 * \brief Setter for call header template. The call header is the text
 * 	displayed before the call log line.
 * \param call_header_template Format of the header used. Can't be NULL.
 */
_YALL_PUBLIC void yall_config_set_call_header_template(
	const char *call_header_template);
	
/**
 * \brief Reset the call header template to the default value.
 */
_YALL_PUBLIC void yall_config_reset_call_header_template(void);

/**
 * \brief Returns the format of the call header currently used.
 * \return Current call header format.
 */
_YALL_PUBLIC const char *yall_config_get_call_header_template(void);

_YALL_PUBLIC void yall_config_set_tab_width(uint8_t tab_width);
_YALL_PUBLIC void yall_config_reset_tab_width(void);
_YALL_PUBLIC uint8_t yall_config_get_tab_width(void);

#endif
