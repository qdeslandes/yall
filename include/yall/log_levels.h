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

#ifndef _LOG_LEVELS_H
#define _LOG_LEVELS_H

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

#endif
