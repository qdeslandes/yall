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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/subsystem.h"

#include <stdlib.h>
#include <string.h>

#include "yall/utils.h"
#include "yall/error.h"
#include "yall/debug.h"

static struct yall_subsystem *subsystems = NULL;

static struct yall_subsystem_params default_params = {
	yall_warning,
	yall_subsys_enable,
	yall_file_output,
	"yall_default.log"
};

/*
 * _get_subsystem : returns the subsystem of the given name. Starting the
 *      research from a subsystem's list. The <params> parameter is used to
 *      stored the parameters of the subsystem gathered through tree crawling.
 *      <name> should not be NULL, but <s> and <params> can be.
 *      Tricky part : when to set the subsystem's parameters ? A brother
 *      subsystem must not think the current parameters are the parent's
 *      parameter it inherit if one of its brother has wrote them. To cover
 *      this possibility, we write the parameters in one of theses to
 *      conditions :
 *	      * If the subsystem has childs. So, if we crawl the childs, the
 *	      given parameters will be the parent's parameter. Wathever the
 *	      depth of the parent could be.
 *	      * If the current subsystem is the research subsystem.
 *      This means that a subsystem could not hide it's parent values unless it
 *      is the researched subsystem.
 */
static struct yall_subsystem *_get_subsystem(const char *name,
	struct yall_subsystem *s,
	struct yall_subsystem_params *params)
{
	for (; s; s = s->next) {
		// Write subsystem's parameters
		if (s->childs || strncmp(s->name, name,
			SUBSYS_NAME_LEN-1) == 0) {

			if (params && s->log_level != yall_inherited_level)
				params->log_level = s->log_level;

			/*
			 * If a parent subsystem is disabled, do not override
			 * the status with a child subsystem.
			 * TODO : We could avoid parsing the tree if we return
			 * once finding a disabled subsystem, but the caller
			 * function must handle it.
			 */
			if (params && s->status != yall_inherited_status
				&& params->status != yall_subsys_disable)
 				params->status = s->status;

			if (params && s->output_type != yall_inherited_output)
				params->output_type = s->output_type;

			if (params && s->output_file)
				params->output_file = s->output_file;
		}

		// Is it the researched subsystem ?
		if (strncmp(s->name, name, SUBSYS_NAME_LEN-1) == 0)
			return s;

		struct yall_subsystem *sc = _get_subsystem(name, s->childs,
			params);

		if (sc)
			return sc;
	}

	return NULL;
}

/*
 * _free_subsystem : free the given subsystem, its name and output file if any.
 *      <s> must not be NULL.
 */
static void _free_subsystem(struct yall_subsystem *s)
{
	free(s->output_file);
	free(s);
}

/*
 * set_default_params : fill the given yall_subsystem_params with the proper
 *      default values defined at the top of this source file inside
 *      default_params. <params> can't be NULL.
 */
static void set_default_params(struct yall_subsystem_params *params)
{
	params->log_level = default_params.log_level;
	params->status = default_params.status;
	params->output_type = default_params.output_type;
	params->output_file = default_params.output_file;
}

/*
 * set_subsys_status : change the status of a subsystem. The subsystem name
 *      can't be NULL. Assignation is atomic.
 */
static void set_subsys_status(
	const char *subsys_name,
	enum yall_subsys_status status)
{
	struct yall_subsystem *s = get_subsystem(subsys_name, NULL);

	if (s)
		s->status = status;
}

void yall_disable_subsystem(const char *subsys_name)
{
	_YALL_DBG_INFO("Disable subsystem %s.", subsys_name);
	set_subsys_status(subsys_name, yall_subsys_disable);
}

void yall_enable_subsystem(const char *subsys_name)
{
	_YALL_DBG_INFO("Enable subsystem %s.", subsys_name);
	set_subsys_status(subsys_name, yall_subsys_enable);
}

struct yall_subsystem *get_subsystem(const char *name,
	struct yall_subsystem_params *params)
{
	if (params)
		set_default_params(params);

	struct yall_subsystem *s = _get_subsystem(name, subsystems, params);

	if (! s) {
		/*
		 * Braces are set here as _YALL_DBG_WARNING could expand to
		 * nothing.
		 */
		_YALL_DBG_WARNING("Could not find subsystem %s.", name);
	}

	return s;
}

struct yall_subsystem *create_subsystem(const char *name,
	enum yall_log_level log_level, enum yall_output_type output_type,
	const char *output_file)
{
	struct yall_subsystem *s = malloc(sizeof(struct yall_subsystem));

	// Set each optional pointer to NULL, to avoid surprises
	s->output_file = NULL;
	s->parent = NULL;
	s->childs = NULL;
	s->previous = NULL;
	s->next = NULL;

	strncpy(s->name, name, SUBSYS_NAME_LEN-1);
	s->name[SUBSYS_NAME_LEN-1] = 0;
	s->log_level = log_level;
	s->output_type = output_type;

	if (output_file) {
		s->output_file = malloc(strlen(output_file) + 1);

		strncpy(s->output_file, output_file, strlen(output_file)+1);

		/*
		 * By default, the old log file will be delete each time the
		 * subsystem is created. This can't be changed currently, but
		 * will be when the library will load parameters from a
		 * configuration file.
		 */
		s->delete_old_log_file = true;
		delete_old_log_file(s->output_file);
	}

	s->status = yall_subsys_enable;

	_YALL_DBG_INFO("Subsystem %s created.", s->name);

	return s;
}

void add_subsystem(const char *parent_name, struct yall_subsystem *s)
{
	struct yall_subsystem *previous = NULL;
	struct yall_subsystem *parent = parent_name ?
		get_subsystem(parent_name, NULL) : NULL;

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

	for ( ; previous->next; previous = previous->next)
		;

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
	 * The subsystem's status does not change.
	 */
	free(s->output_file);
	s->output_file = NULL;

	s->log_level = log_level;
	s->output_type = output_type;

	s->parent = NULL;
	s->childs = NULL;
	s->previous = NULL;
	s->next = NULL;

	if (output_file)
		s->output_file = strdup(output_file);
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

		/*
		 * Some pointer are set to NULL here, we can not skip this step
		 * as these pointers will be used to detect is some following
		 * subsystems must be freed.
		 */
		s->next = NULL;
		s->previous = NULL;
		s->parent = NULL;

		_YALL_DBG_INFO("Subsystem %d removed.", name);
	}

	return s;
}

void _free_subsystems(struct yall_subsystem *s)
{
	_YALL_DBG_INFO("Cleaning subsystems.");

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

void free_subsystems(void)
{
	_free_subsystems(subsystems);
}
