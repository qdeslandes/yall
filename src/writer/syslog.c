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

#include "yall/writer/syslog.h"

#include <string.h>
#ifdef __linux__
#include <syslog.h>
#endif

static const char *syslog_facility_str[25] = {
	"yall_fac_kern",
	"yall_fac_user",
	"yall_fac_mail",
	"yall_fac_daemon",
	"yall_fac_auth",
	"yall_fac_syslog",
	"yall_fac_lpr",
	"yall_fac_news",
	"yall_fac_uucp",
	"yall_fac_cloc",
	"yall_fac_authpriv",
	"yall_fac_ftp",
	"yall_fac_ntp",
	"yall_fac_audit",
	"yall_fac_alert",
	"yall_fac_cron",
	"yall_fac_local0",
	"yall_fac_local1",
	"yall_fac_local2",
	"yall_fac_local3",
	"yall_fac_local4",
	"yall_fac_local5",
	"yall_fac_local6",
	"yall_fac_local7",
	"yall_fac_inherited",
};

/**
 * \brief From a yall log level it returns the syslog corresponding one, as the
 *	order between the two libraries is reversed. There is no reason to have
 *	it reversed, but it is not in the scope of the current feature.
 * \param log_level yall log level.
 * \return Integer corresponding to the propre syslog log level.
 */
static int get_syslog_level(enum yall_log_level ll)
{
#ifdef __linux__
	static int syslog_ll[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING,
		LOG_ERR, LOG_CRIT, LOG_ALERT };

	return syslog_ll[ll];
#else
	return yall_fac_user;
#endif
}

enum yall_syslog_facility str_to_syslog_facility(const char *s)
{
	for (int i = 0; i < 25; ++i) {
		if (strcmp(syslog_facility_str[i], s) == 0)
			return i;
	}

	return yall_fac_user;
}

void write_log_syslog(enum yall_log_level log_level, const char *msg)
{
#ifdef __linux__
	syslog(LOG_MAKEPRI(LOG_LOCAL1, get_syslog_level(log_level)),
		msg);
#else
#endif
}
