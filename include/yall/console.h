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

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <stdint.h>

#include "yall/log_levels.h"

/*
 * write_log_console : write the log message on the console. The message can't
 * 	be NULL. The color of the message depend of the log level and the color
 * 	associated to this log level inside the source file. Also, <log_level>
 * 	must be different from yall_inherited_level.
 */
uint8_t write_log_console(enum yall_log_level log_level, const char *msg);

#endif
