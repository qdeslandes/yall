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

#include "yall/subsystem.h"

#include <stdlib.h>
#include <string.h>

#include "yall/utils.h"
#include "yall/errors.h"

static struct yall_subsystem *subsystems = NULL;

static struct yall_subsystem_params default_params = {
	yall_warning,
	yall_file_output,
	"app.log"
};

/*
 * _get_subsystem : returns the subsystem of the given name. Starting the
 * 	research from a subsystem's list. The <params> parameter is used to
 * 	stored the parameters of the subsystem gathered through tree crawling.
 * 	<name> should not be NULL, but <s> and <params> can be.
 * 	Tricky part : when to set the subsystem's parameters ? A brother
 * 	subsystem must not think the current parameters are the parent's
 * 	parameter it inherit if one of its brother has wrote them. To cover
 * 	this possibility, we write the parameters in one of theses to
 * 	conditions :
 * 		* If the subsystem has childs. So, if we crawl the childs, the
 * 		given parameters will be the parent's parameter. Wathever the
 * 		depth of the parent could be.
 * 		* If the current subsystem is the research subsystem.
 * 	This means that a subsystem could not hide it's parent values unless it
 * 	is the researched subsystem.
 */
static struct yall_subsystem *_get_subsystem(const char *name,
	struct yall_subsystem *s,
	struct yall_subsystem_params *params)
{
	for (; s; s = s->next) {
		// Write subsystem's parameters
		if (s->childs || strcmp(s->name, name) == 0) {
			if (params && s->log_level != yall_inherited_level)
				params->log_level = s->log_level;

			if (params && s->output_type != yall_inherited_output)
				params->output_type = s->output_type;

			if (params && s->output_file)
				params->output_file = s->output_file;
		}

		// Is it the researched subsystem ?
		if (strcmp(s->name, name) == 0)
			return s;

		struct yall_subsystem *sc = _get_subsystem(name, s->childs, params);

		if (sc)
			return sc;
	}

	return NULL;
}

/*
 * _free_subsystem : free the given subsystem, its name and output file if any.
 * 	<s> must not be NULL.
 */
static void _free_subsystem(struct yall_subsystem *s)
{
	free(s->output_file);
	free(s->name);
	free(s);
}

/*
 * _free_subsystems : free the given subsystems tree through _free_subsystem
 * 	function. <s> is used as the root of the tree, so its parents will not
 * 	be freed.
 */
static void _free_subsystems(struct yall_subsystem *s)
{
	while (s) {
		struct yall_subsystem *tmp = s->next;

		if (s->parent)
			s->parent->childs = NULL;

		if (s->childs)
			_free_subsystems(s->childs);

		_free_subsystem(s);
		s = tmp;
	}
}

/*
 * set_default_params : fill the given yall_subsystem_params with the proper
 * 	default values defined at the top of this source file inside
 * 	default_params. <params> can't be NULL.
 */
static void set_default_params(struct yall_subsystem_params *params)
{
	params->log_level = default_params.log_level;
	params->output_type = default_params.output_type;
	params->output_file = default_params.output_file;
}

struct yall_subsystem *get_subsystem(const char *name,
	struct yall_subsystem_params *params)
{
	if (params)
		set_default_params(params);

	return _get_subsystem(name, subsystems, params);
}

struct yall_subsystem *create_subsystem(const char *name,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file)
{
	struct yall_subsystem *s = NULL;

	if (! (s = malloc(sizeof(struct yall_subsystem))))
		goto err;

	// Set each optional pointer to NULL, to avoid surprises
	s->output_file = NULL;
	s->parent = NULL;
	s->childs = NULL;
	s->previous = NULL;
	s->next = NULL;

	// Copy name and parameters
	if (! (s->name = malloc(strlen(name) + 1)))
		goto err_free;

	strncpy(s->name, name, strlen(name)+1);
	s->log_level = log_level;
	s->output_type = output_type;

	if (output_file) {
		if (! (s->output_file = malloc(strlen(output_file) + 1)))
			goto err_free_name;

		strncpy(s->output_file, output_file, strlen(output_file)+1);
	}

	return s;

err_free_name:
	free(s->name);
err_free:
	free(s);
err:
	return NULL;
}

void add_subsystem(const char *parent_name, struct yall_subsystem *s)
{
	struct yall_subsystem *previous = NULL;
	struct yall_subsystem *parent = parent_name ? get_subsystem(parent_name, NULL) : NULL;

	// Assign parent to <s>, no problem if parent is NULL
	s->parent = parent;

	// If the subsystem is a list head or sublist head
	if (! subsystems) {
		subsystems = s;
		return;
	}

	if (parent && ! parent->childs) {
		parent->childs = s;
		return;
	}

	// Coming to this point means the subsystem must be added at the end
	// of a subsystems list.
	previous = parent ? parent->childs : subsystems;

	for ( ; previous->next; previous = previous->next) ;

	previous->next = s;
	s->previous = previous;
}

void update_subsystem(struct yall_subsystem *s,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file)
{
	/*
	 * Always free output_file of the subsystem. It will be replaced in
	 * every case.
	 */
	free(s->output_file);
	s->output_file = NULL;

	s->log_level = log_level;
	s->output_type = output_type;

	if (output_file && (s->output_file = malloc(strlen(output_file) + 1)))
		strncpy(s->output_file, output_file, strlen(output_file)+1);
}

struct yall_subsystem *remove_subsystem(const char *name)
{
	struct yall_subsystem *s = get_subsystem(name, NULL);

	if (s) {
		// Link the previous to the next
		if (s->previous)
			s->previous->next = s->next;

		// Link the next to the previous
		if (s->next)
			s->next->previous = s->previous;

		// If 1st child, link the parent to the second child
		if (s->parent && s->parent->childs == s)
			s->parent->childs = s->next;

		if (subsystems == s)
			subsystems = s->next;
	}

	return s;
}

void free_subsystems(void)
{
	_free_subsystems(subsystems);
}
