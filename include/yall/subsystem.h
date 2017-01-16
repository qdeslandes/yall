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

#ifndef _SUBSYSTEM_H
#define _SUBSYSTEM_H

#include <stdint.h>

#include "yall/log_levels.h"
#include "yall/output_types.h"

struct yall_subsystem {
	char *name;
	enum yall_log_level log_level;
	enum yall_output_type output_type;
	char *output_file;
	struct yall_subsystem *parent;
	struct yall_subsystem *childs;
	struct yall_subsystem *previous;
	struct yall_subsystem *next;
};

struct yall_subsystem_params {
	enum yall_log_level log_level;
	enum yall_output_type output_type;
	const char *output_file;
};


/*
 * get_subsystem : if a subsystem of the given <name> is available,
 * 	returns it. If not, the function returns NULL.
 * 	<name> can not be NULL and must be a NULL terminated string.
 */
struct yall_subsystem *get_subsystem(const char *name,
	struct yall_subsystem_params *params);

/*
 * create_subsystem : returns a newly create subsystem. <name> must not be NULL
 * 	and must be a NULL terminated string. On error, NULL is returned.
 */
struct yall_subsystem *create_subsystem(const char *name,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file);

/*
 * add_subsystem : add the given subsystem to the subsystem's tree. Handle
 * 	inheritance. If parent is NULL or not found, the subsystem will be
 * 	added to the top-level tree. No subsystem with the new subsystem's
 * 	name should be present in the tree. <s> must not be NULL. <parent>
 * 	can be NULL or a NULL terminated string.
 */
void add_subsystem(const char *parent, struct yall_subsystem *s);

/*
 * update_subsystem : update a given subsystem. <s> can't be NULL.
 */
void update_subsystem(struct yall_subsystem *s,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file);

/*
 * remove_subsystem : remove a subsystem from the subsystem tree. <name> can
 * 	not be NULL. If the subsystem is found, returns it, otherwise returns
 * 	NULL and must be a NULL terminated string.
 */
struct yall_subsystem *remove_subsystem(const char *name);

/*
 * free_subsystems : free the library's subsystems list.
 */
void free_subsystems(void);

#endif
