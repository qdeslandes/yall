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

#ifndef _YALL_LOG_H
#define _YALL_LOG_H

#include "yall/utils.h"

/*
 * Theses macros are used to generate log messages. There is two types of
 *      logs :
 *      * YALL_<log_level>(<subsystem>, <format>, ...) : which will print
 *	      the log message according the given subsystem's parameters.
 *	      If the subsystem does not exists, default parameters are
 *	      used. <format> is a printf() like format, with the parameters.
 *      * YALL_<log_level>_IF(<subsystem>, <condition>, <format>, ...) : same
 *	      function as the previous, but the log will be processed only
 *	      if the condition is true.
 *      * YALL_CALL_<log_level>(<subsystem>, <function>, <args>) : with these
 *	      macros, the format of the message will be handled by the given
 *	      function. <function> will be called with <args> as parameters.
 *      * YALL_CALL_<log_level>_IF(<subsystem>, <expr>, <function>, <args>) :
 *	      same function as the previous, except that the message will if
 *	      created and displayed only if <expr> evaluates to true.
 *
 * The _YALL_LOG(<...>) wrapper is used to handle C++ stream operators. This
 *      way, on a C++ compiler, we can call the logging function like :
 *	      YALL_DEBUG(sub, "This is " << "my log " << "msg");
 */

#if (_MSC_VER == 1800)
#	define __func__ __FUNCTION__
#endif

#define FUNCTION __func__

#ifndef __cplusplus
#	define _YALL_LOG(subsystem, log_level, ...) \
		do { \
			yall_log(subsystem, log_level, FUNCTION, ##__VA_ARGS__); \
		} while (0)

#	define _YALL_CALL_LOG(subsystem, log_level, function, args) \
	do { \
		yall_call_log(subsystem, log_level, FUNCTION, function, args); \
	} while (0)
#else
#	define _YALL_LOG(subsystem, log_level, msg) \
		do { \
			std::ostringstream oss; \
			oss << msg; \
			yall_log(subsystem, log_level, FUNCTION, oss.str().c_str()); \
		} while (0)

#	define _YALL_CALL_LOG(subsystem, log_level, function, args) \
		do { \
			Yall::getInstance().__callLog(subsystem, log_level, FUNCTION, function, args); \
		} while (0)
#endif

#define YALL_EMERG(subsystem, ...)      \
	_YALL_LOG(subsystem, yall_emerg, ##__VA_ARGS__)
#define YALL_ALERT(subsystem, ...)      \
	_YALL_LOG(subsystem, yall_alert, ##__VA_ARGS__)
#define YALL_CRIT(subsystem, ...)	       \
	_YALL_LOG(subsystem, yall_crit, ##__VA_ARGS__)
#define YALL_ERR(subsystem, ...) \
	_YALL_LOG(subsystem, yall_err, ##__VA_ARGS__)
#define YALL_WARNING(subsystem, ...) \
	_YALL_LOG(subsystem, yall_warning, ##__VA_ARGS__)
#define YALL_NOTICE(subsystem, ...) \
	_YALL_LOG(subsystem, yall_notice, ##__VA_ARGS__)
#define YALL_INFO(subsystem, ...) \
	_YALL_LOG(subsystem, yall_info, ##__VA_ARGS__)
#define YALL_DEBUG(subsystem, ...) \
	_YALL_LOG(subsystem, yall_debug, ##__VA_ARGS__)

#define YALL_EMERG_IF(subsystem, expr, ...) \
	_YALL_IF(subsystem, expr, yall_emerg, ##__VA_ARGS__)
#define YALL_ALERT_IF(subsystem, expr, ...) \
	_YALL_IF(subsystem, expr, yall_alert, ##__VA_ARGS__)
#define YALL_CRIT_IF(subsystem, expr, ...)	      \
	_YALL_IF(subsystem, expr, yall_crit, ##__VA_ARGS__)
#define YALL_ERR_IF(subsystem, expr, ...) \
	_YALL_IF(subsystem, expr, yall_err, ##__VA_ARGS__)
#define YALL_WARNING_IF(subsystem, expr, ...) \
	_YALL_IF(subsystem, expr, yall_warning, ##__VA_ARGS__)
#define YALL_NOTICE_IF(subsystem, expr, ...) \
	_YALL_IF(subsystem, expr, yall_notice, ##__VA_ARGS__)
#define YALL_INFO_IF(subsystem, expr, ...) \
	_YALL_IF(subsystem, expr, yall_info, ##__VA_ARGS__)
#define YALL_DEBUG_IF(subsystem, expr, ...) \
	_YALL_IF(subsystem, expr, yall_debug, ##__VA_ARGS__)

#define _YALL_IF(subsystem, expr, log_level, ...) \
	do { \
		if ((expr)) \
			_YALL_LOG(subsystem, log_level, ##__VA_ARGS__); \
	} while (0)

#define YALL_CALL_EMERG(subsystem, function, args)      \
	_YALL_CALL_LOG(subsystem, yall_emerg, function, args)
#define YALL_CALL_ALERT(subsystem, function, args)      \
	_YALL_CALL_LOG(subsystem, yall_alert, function, args)
#define YALL_CALL_CRIT(subsystem, function, args)	       \
	_YALL_CALL_LOG(subsystem, yall_crit, function, args)
#define YALL_CALL_ERR(subsystem, function, args) \
	_YALL_CALL_LOG(subsystem, yall_err, function, args)
#define YALL_CALL_WARNING(subsystem, function, args) \
	_YALL_CALL_LOG(subsystem, yall_warning, function, args)
#define YALL_CALL_NOTICE(subsystem, function, args) \
	_YALL_CALL_LOG(subsystem, yall_notice, function, args)
#define YALL_CALL_INFO(subsystem, function, args) \
	_YALL_CALL_LOG(subsystem, yall_info, function, args)
#define YALL_CALL_DEBUG(subsystem, function, args) \
	_YALL_CALL_LOG(subsystem, yall_debug, function, args)

#define YALL_CALL_EMERG_IF(subsystem, expr, function, args) \
	_YALL_CALL_IF(subsystem, expr, yall_emerg, function, args)
#define YALL_CALL_ALERT_IF(subsystem, expr, function, args) \
	_YALL_CALL_IF(subsystem, expr, yall_alert, function, args)
#define YALL_CALL_CRIT_IF(subsystem, expr, function, args) \
	_YALL_CALL_IF(subsystem, expr, yall_crit, function, args)
#define YALL_CALL_ERR_IF(subsystem, expr, function, args) \
	_YALL_CALL_IF(subsystem, expr, yall_err, function, args)
#define YALL_CALL_WARNING_IF(subsystem, expr, function, args) \
	_YALL_CALL_IF(subsystem, expr, yall_warning, function, args)
#define YALL_CALL_NOTICE_IF(subsystem, expr, function, args) \
	_YALL_CALL_IF(subsystem, expr, yall_notice, function, args)
#define YALL_CALL_INFO_IF(subsystem, expr, function, args) \
	_YALL_CALL_IF(subsystem, expr, yall_info, function, args)
#define YALL_CALL_DEBUG_IF(subsystem, expr, function, args) \
	_YALL_CALL_IF(subsystem, expr, yall_debug, function, args)

#define _YALL_CALL_IF(subsystem, expr, log_level, function, args) \
	do { \
		if ((expr)) \
			_YALL_CALL_LOG(subsystem, log_level, function, args); \
	} while (0)

#endif