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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _YALL_SUBSYSTEM_H
#define _YALL_SUBSYSTEM_H

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>

#include "yall/utils.h"
#include "yall/file.h"
#include "yall/status.h"
#include "yall/log_levels.h"
#include "yall/output_types.h"

#define SUBSYS_NAME_LEN		16

struct yall_subsystem {
	char name[SUBSYS_NAME_LEN];
	enum yall_log_level log_level;
	_Atomic enum yall_subsys_status status;
	enum yall_output_type output_type;
	char *output_file;
	bool delete_old_log_file;
	struct yall_subsystem *parent;
	struct yall_subsystem *childs;
	struct yall_subsystem *previous;
	struct yall_subsystem *next;
};

struct yall_subsystem_params {
	enum yall_log_level log_level;
	enum yall_subsys_status status;
	enum yall_output_type output_type;
	const char *output_file;
};

/*
 * yall_disable_subsystem : this disable a given subsystem. The given name
 *	can't be NULL. This function can be called from different threads.
 */
_YALL_PUBLIC void yall_disable_subsystem(const char *subsys_name);

/*
 * yall_enable_subsystem : this enable a given subsystem. The given name can't
 *	be NULL. This function can be called from different threads.
 */
_YALL_PUBLIC void yall_enable_subsystem(const char *subsys_name);

/*
 * get_subsystem : if a subsystem of the given <name> is available,
 * 	returns it. If not, the function returns NULL.
 * 	<name> can not be NULL and must be a NULL terminated string.
 * 	<params> is a struct which will contains the subsystem's parameters.
 * 	It will be filled with the default parameters in case some parameters
 * 	are missing in the subsystem's.
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
 * remove_subsystem : remove a subsystem from the subsystem tree. If this
 *  subsystem had childs, its childs will always be linked to it <name> can
 * 	not be NULL. If the subsystem is found, returns it, otherwise returns
 * 	NULL and must be a NULL terminated string.
 */
struct yall_subsystem *remove_subsystem(const char *name);

/*
 * free_subsystems : free the library's subsystems list.
 */
void free_subsystems(void);

#endif
