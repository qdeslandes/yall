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
 * \var yall_syslog_facility::yall_fac_ntp
 *	\brief NTP subsystem.
 * \var yall_syslog_facility::yall_fac_audit
 *	\brief Log audit.
 * \var yall_syslog_facility::yall_fac_alert
 *	\brief Log alert.
 * \var yall_syslog_facility::yall_fac_cron
 *	\brief Clock daemon.
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
 * \var yall_syslog_facility::yall_fac_inherited
 *	\brief Used to defined inheritance between subsystems.
 */
enum yall_syslog_facility {
	yall_fac_kern,
	yall_fac_user,
	yall_fac_mail,
	yall_fac_daemon,
	yall_fac_auth,
	yall_fac_syslog,
	yall_fac_lpr,
	yall_fac_news,
	yall_fac_uucp,
	yall_fac_cloc,
	yall_fac_authpriv,
	yall_fac_ftp,
	yall_fac_ntp,
	yall_fac_audit,
	yall_fac_alert,
	yall_fac_cron,
	yall_fac_local0,
	yall_fac_local1,
	yall_fac_local2,
	yall_fac_local3,
	yall_fac_local4,
	yall_fac_local5,
	yall_fac_local6,
	yall_fac_local7,
	yall_fac_inherited
};

enum yall_syslog_facility str_to_syslog_facility(const char *s);
void write_log_syslog(enum yall_log_level log_level, const char *msg);

#endif
