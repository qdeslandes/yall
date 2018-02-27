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

#ifndef _YALL_LOG_LEVELS_H
#define _YALL_LOG_LEVELS_H

/**
 * \enum yall_log_level
 * \brief This enumerator stores the different log level used by the library.
 *	They are extracted from the Syslog protocol (RFC 5424). The last one :
 *	yall_inherited_level is used to inform that a subsystem inherit its log
 *	level from its parent.
 */
enum yall_log_level {
	yall_debug,
	yall_info,
	yall_notice,
	yall_warning,
	yall_err,
	yall_crit,
	yall_alert,
	yall_emerg,
	yall_inherited_level
};

/**
 * \brief From a log level, it returns its name as a nul-terminated string. This
 *	string must not be freed. This function is used in log messages to get
 *	the explicit log level string capitalized, without "yall" prefix.
 * \param log_level Log level we want the name.
 * \return Log level as a string.
 */
const char *get_log_level_name(enum yall_log_level log_level);

/**
 * \brief Returns the log level corresponding to the given log level string.
 * \param str Log level as a string.
 * \retun Log level as a yall_log_level.
 */
enum yall_log_level str_to_log_level(const char *str);

#endif
