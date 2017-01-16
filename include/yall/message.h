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

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <stdint.h>
#include <stdarg.h>

#include "yall/log_levels.h"

#define YALL_MSG_LEN	512

uint8_t generate_message(char *buffer,
	const char *format,
	const char *subsystem,
	enum yall_log_level log_level,
	const char *function,
	va_list args);

#endif
