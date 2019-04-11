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

#ifndef _YALL_WRITER_SYSLOG_H
#define _YALL_WRITER_SYSLOG_H

#include <stdint.h>
#include <syslog.h>

#include "yall/error.h"
#include "yall/output/types.h"
#include "yall/log_level.h"

/**
 * \enum yall_syslog_facility
 * \brief This enum stores all the possible syslog facilities. These facilities
 *	are standardized, so there is not problem to set custom name for it if
 *	attached values are not changed.
 * \var yall_syslog_facility::yall_fac_kern
 *	\brief Kernel messages
 * \var yall_syslog_facility::yall_fac_user
 *	\brief User level messages.
 * \var yall_syslog_facility::yall_fac_mail
 *	\brief Mail system.
 * \var yall_syslog_facility::yall_fac_daemon
 *	\brief System daemons.
 * \var yall_syslog_facility::yall_fac_auth
 *	\brief Security / authorization messages.
 * \var yall_syslog_facility::yall_fac_syslog
 *	\brief Message generated internally by syslogd.
 * \var yall_syslog_facility::yall_fac_lpr
 *	\brief Line printer subsystem.
 * \var yall_syslog_facility::yall_fac_news
 *	\brief Network news subsystem.
 * \var yall_syslog_facility::yall_fac_uucp
 *	\brief UUCP subsystem.
 * \var yall_syslog_facility::yall_fac_cloc
 *	\brief Clock daemon.
 * \var yall_syslog_facility::yall_fac_authpriv
 *	\brief Security / authorization messages.
 * \var yall_syslog_facility::yall_fac_ftp
 *	\brief FTP daemon.
 * \var yall_syslog_facility::yall_fac_local0
 *	\brief Local use 0.
 * \var yall_syslog_facility::yall_fac_local1
 *	\brief Local use 1.
 * \var yall_syslog_facility::yall_fac_local2
 *	\brief Local use 2.
 * \var yall_syslog_facility::yall_fac_local3
 *	\brief Local use 3.
 * \var yall_syslog_facility::yall_fac_local4
 *	\brief Local use 4.
 * \var yall_syslog_facility::yall_fac_local5
 *	\brief Local use 5.
 * \var yall_syslog_facility::yall_fac_local6
 *	\brief Local use 6.
 * \var yall_syslog_facility::yall_fac_local7
 *	\brief Local use 7.
 */

enum yall_syslog_facility {
	yall_fac_kern = LOG_KERN,
	yall_fac_user = LOG_USER,
	yall_fac_mail = LOG_MAIL,
	yall_fac_daemon = LOG_DAEMON,
	yall_fac_auth = LOG_AUTH,
	yall_fac_syslog = LOG_SYSLOG,
	yall_fac_lpr = LOG_LPR,
	yall_fac_news = LOG_NEWS,
	yall_fac_uucp = LOG_UUCP,
	yall_fac_cloc = LOG_CRON,
	yall_fac_authpriv = LOG_AUTHPRIV,
	yall_fac_ftp = LOG_FTP,
	yall_fac_local0 = LOG_LOCAL0,
	yall_fac_local1 = LOG_LOCAL1,
	yall_fac_local2 = LOG_LOCAL2,
	yall_fac_local3 = LOG_LOCAL3,
	yall_fac_local4 = LOG_LOCAL4,
	yall_fac_local5 = LOG_LOCAL5,
	yall_fac_local6 = LOG_LOCAL6,
	yall_fac_local7 = LOG_LOCAL7
};

/**
 * \brief Convert the given string to the corresponding yall syslog facility.
 * \param s Syslog facility as string. It should contain the facility using the
 *	same name a available un yall_syslog_facility enumerator.
 * \return Value of type yall_syslog_facility
 */
enum yall_syslog_facility str_to_syslog_facility(const char *s);

/**
 * \brief Write the given message using syslog mechanism. The log level is used
 *	to compute the message priority inside syslog, through LOG_MAKEPRI()
 *	macro.
 * \param log_level Log level to use to write the log message.
 * \param msg Log message to write using syslog.
 */
void write_log_syslog(enum yall_log_level log_level, const char *msg);

#endif
