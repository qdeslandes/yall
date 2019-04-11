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
#include <syslog.h>

#include "yall/config/parameters.h"

#define NB_FACILITIES 20

struct {
	const char *str;
	int32_t value;
} syslog_facilities_set[] = {
	{ "yall_fac_kern", LOG_KERN },
	{ "yall_fac_user", LOG_USER },
	{ "yall_fac_mail", LOG_MAIL },
	{ "yall_fac_daemon", LOG_DAEMON },
	{ "yall_fac_auth", LOG_AUTH },
	{ "yall_fac_syslog", LOG_SYSLOG },
	{ "yall_fac_lpr", LOG_LPR },
	{ "yall_fac_news", LOG_NEWS },
	{ "yall_fac_uucp", LOG_UUCP },
	{ "yall_fac_cloc", LOG_CRON },
	{ "yall_fac_authpriv", LOG_AUTHPRIV },
	{ "yall_fac_ftp", LOG_FTP },
	{ "yall_fac_local0", LOG_LOCAL0 },
	{ "yall_fac_local1", LOG_LOCAL1 },
	{ "yall_fac_local2", LOG_LOCAL2 },
	{ "yall_fac_local3", LOG_LOCAL3 },
	{ "yall_fac_local4", LOG_LOCAL4 },
	{ "yall_fac_local5", LOG_LOCAL5 },
	{ "yall_fac_local6", LOG_LOCAL6 },
	{ "yall_fac_local7", LOG_LOCAL7 }
};

/**
 * \brief From a yall log level it returns the syslog corresponding one, as the
 *	order between the two libraries is reversed. There is no reason to have
 *	it reversed, but it is not in the scope of the current feature.
 * \param log_level yall log level.
 * \return Integer corresponding to the propre syslog log level.
 */
static uint8_t get_syslog_level(enum yall_log_level ll)
{
	static uint8_t syslog_ll[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE,
		LOG_WARNING, LOG_ERR, LOG_CRIT, LOG_ALERT , LOG_EMERG };

	return syslog_ll[ll];
}

enum yall_syslog_facility str_to_syslog_facility(const char *s)
{
	for (uint8_t i = 0; i < NB_FACILITIES; ++i) {
		if (strcmp(syslog_facilities_set[i].str, s) == 0)
			return syslog_facilities_set[i].value;
	}

	return yall_fac_user;
}

void write_log_syslog(enum yall_log_level log_level, const char *msg)
{
	syslog((int32_t)LOG_MAKEPRI((int32_t)yall_config_get_syslog_facility(),
		(int32_t)get_syslog_level(log_level)), msg);
}
