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

#ifndef _WRITER_H
#define _WRITER_H

#include <stdint.h>

#include "yall/output_types.h"
#include "yall/log_levels.h"

/*
 * writer_init : initialize some stuff for the console and file writers.
 * 	Currently initialize the semaphores. This should be called once.
 */
uint8_t writer_init(void);

/*
 * write : write the message to the output medium. Returns a YALL_ERROR on
 * 	error. <msg> must not be NULL, but <output_file> can if <output_type>
 * 	is equals to yall_file_output or yall_both_output.
 */
uint8_t write_msg(enum yall_output_type output_type,
	enum yall_log_level log_level,
	const char *output_file,
	const char *msg);

/*
 * writer_destroy : destroy all the writers semaphores.
 */
void writer_close(void);

#endif
