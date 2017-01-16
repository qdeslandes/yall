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

#ifndef _ERRORS_H
#define _ERRORS_H

#define YALL_OK			0x00

#define YALL_ALREADY_INIT	0x10
#define YALL_NOT_INIT		0x11
#define YALL_SEM_INIT_ERR	0x12
#define YALL_NO_MEM		0x13
#define YALL_LOG_LEVEL_TOO_LOW	0x14

#define YALL_NO_NAME		0x20

#define YALL_FILE_LOCK_ERR	0x30
#define YALL_FILE_OPEN_ERR	0x31

#define YALL_CONSOLE_LOCK_ERR	0x40
#define YALL_CONSOLE_WRITE_ERR	0x41

#define YALL_STRING_WRITE_ERR	0x50

#define YALL_SUBSYS_NOT_EXISTS	0x60

#endif
