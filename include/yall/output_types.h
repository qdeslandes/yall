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

#ifndef _OUTPUT_TYPES_H
#define _OUTPUT_TYPES_H

/*
 * Theses values should always be powers of 2. This way we can easily define
 * target that will handle 2, 3 or more output types at once.
 */
enum yall_output_type {
	yall_inherited_output	= 0,
	yall_console_output 	= 1 << 0,
	yall_file_output 	= 1 << 1
};

#endif
