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

#ifndef _UTILS_H
#define _UTILS_H

#ifdef __linux__
#   define _YALL_PUBLIC 	__attribute__((visibility("default")))
#elif _WIN32
#   define _YALL_PUBLIC 	__declspec(dllexport)
#   if (_MSC_VER == 1800)
#       define snprintf _snprintf
#   endif
#endif

#endif
