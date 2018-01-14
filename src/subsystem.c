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
#include "yall/writer/file.h"
#include "yall/error.h"
#include "yall/debug.h"

static struct yall_subsystem *subsystems = NULL;

static struct yall_subsystem_params default_params = {
	yall_warning,
	yall_subsys_enable,
	yall_file_output,
	"yall_default.log"
};

/**
 * \struct yall_subsystem
 * \brief This structure contains all the parameters and configuration for a
 *	given subsystem.
 * \var yall_subsystem::name
 *	\brief Name of the subsystem, can't be longer than SUBSYS_NAME_LEN
 *	(including nul-terminating character).
 * \var yall_subsystem::log_level
 *	\brief Minimum log level for this subsystem. All log messages with a
 *	lower log level will be discarded.
 * \var yall_subsystem::status
 *	\brief Status of the subsystem. Used as an atomic variable on linux.
 *	See enum yall_subsys_status for more.
 * \var yall_subsystem::output_type
 *	\brief Defined output type for the subsystem. See enum yall_output_type
 *	for more.
 * \var yall_subsystem::output_file
 *	\brief File in which log will be wrote is output type is
 *	yall_file_ouput.
 * \var yall_subsystem::parent
 *	\brief Parent of the subsystem, can be NULL. If this value is set,
 *	yall_inherited_xxxx can be set to some of the subsystem's parameters.
 * \var yall_subsystem::childs
 *	\brief List of the subsystem's childs, if any.
 * \var yall_subsystem::previous
 *	\brief Previous subsystem in the list.
 * \var yall_subsystem::next
 *	\brief Next subsystem in the list.
 */
struct yall_subsystem {
	char name[SUBSYS_NAME_LEN];
	enum yall_log_level log_level;
#ifdef __linux__
	_Atomic enum yall_subsys_status status;
#elif _WIN32
	enum yall_subsys_status status;
#endif
	enum yall_output_type output_type;
	char *output_file;
	bool delete_old_log_file;
	struct yall_subsystem *parent;
	struct yall_subsystem *childs;
	struct yall_subsystem *previous;
	struct yall_subsystem *next;
};

/**
 * \brief Returns the subsystem of the given name. Starting the research from a
 *	subsystem's list. The *params* parameter is used to store the parameters
 *	of the subsystem gathered through tree crawling.
 * \bug There is a possible flaw in this function :
 *	- subsystem0
 *	  |- subsystem1
 *	  |  |- child0
 *	  |- subsystem2
 *	     |- child1
 *	This way, if subsystem0 defines a property and subsystem1 redefine it,
 *	then subsystem2 possibly can't inherit it from subsystem0. This should
 *	be possible because both subsystems have childs.
 * \param name Name of the subsystem to find inside the tree. Can't be NULL.
 * \param s Subsystems list to search through.
 * \param params Structure yall_subsystem_params used to store the searched
 *	subsystem's parameters. Filled through tree crawling.
 * \return Pointer to the requested subsystem or NULL if not found.
 */
static struct yall_subsystem *_get_subsystem(const char *name,
	struct yall_subsystem *s, struct yall_subsystem_params *params)
{
	struct yall_subsystem *req_subsys = NULL;

	if (! s)
		return NULL;

	if (strncmp(s->name, name, SUBSYS_NAME_LEN-1) == 0) {

		if (params) {
			params->log_level = s->log_level;
			params->status = s->status;
			params->output_type = s->output_type;
			params->output_file = s->output_file;
		}

		return s;
	}

	req_subsys = _get_subsystem(name, s->childs, params);

	if (req_subsys) {
		if (params && params->log_level == yall_inherited_level)
			params->log_level = s->log_level;

		if (params && params->status == yall_inherited_status)
			params->status = s->status;

		if (params && params->output_type == yall_inherited_output)
			params->output_type = s->output_type;

		if(params && params->output_file == NULL)
			params->output_file = s->output_file;

		return req_subsys;
	}

	return _get_subsystem(name, s->next, params);
}

/**
 * \brief Free the given subsystem, and its output file if any.
 * \param s Subsystem to be freed. Can't be NULL.
 */
static void _free_subsystem(struct yall_subsystem *s)
{
	free(s->output_file);
	free(s);
}

/**
 * \brief Fill the given structure yall_subsystem_params with the proper default
 *	values.
 * \param params Structure yall_subsystem_params to be filled with the default
 *	parameters. Can't be NULL.
 */
static void set_default_params(struct yall_subsystem_params *params)
{
	params->log_level = default_params.log_level;
	params->status = default_params.status;
	params->output_type = default_params.output_type;
	params->output_file = default_params.output_file;
}

/**
 * \brief Change the status of the given subsystem.
 * \param subsys_name Name of the subsystem to change the status. Can't be NULL.
 * \param status New status of the subsystem.
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

	if (! s)
		_YALL_DBG_WARNING("Could not find subsystem %s.", name);

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

	// Assign parent to *s*, no problem if parent is NULL
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

/**
 * \brief Subsystems are sets in a tree way. Given a subsystem (*s* here), it
 *	returns the next subsystem. Calling this function with the previously
 *	returned subsystem will allow to browse the subsystems tree. Once
 *	get_next_subsystem() returns NULL, all the subsystems have been
 *	returned.
 * \param s Subsystem from which we need to return the next one in the tree.
 * \param crawl_childs Whether the function should go down the childs lists. It
 *	is used on recursive calls to ensure, from a given subsystem, the
 *	function won't go back into its childs list multiple times.
 * \param d Depth of the subsystem from the base of the tree.
 * \return The next subsystem or NULL if there is no next subsystem.
 */
static struct yall_subsystem *get_next_subsystem(struct yall_subsystem *s,
	bool crawl_childs, int8_t *d)
{
	if (! s)
		return NULL;

	if (crawl_childs && s->childs)
		return ++(*d), s->childs;

	if (s->next)
		return s->next;

	--(*d);

	return get_next_subsystem(s->parent, false, d);
}

enum {
	VERTICAL,
	VERTICAL_RIGHT,
	LIGHT_UP_RIGHT,
	EMPTY
};

#ifdef __linux__
static const char *connectors[4] = {
	"│   ",
	"├── ",
	"└── ",
	"    "};
#else
static const char *connectors[4] = {
	"|   ",
	"|-- ",
	"|-- ",
	"    " };
#endif

/**
 * \brief Call function use with _YALL_DBG_CALL_xxx to disable the subsystems
 *	tree.
 * \param d Structure yall_call_data, used to fill output.
 * \param args Unused here.
 */
static void show_subsystems_tree_call(struct yall_call_data *d,
	const void *args)
{
	UNUSED(args);

	uint8_t curr_indent = 0;
	int8_t indent = 0;
	const char *op[32] = { 0 };
	size_t buff_size = 0;
	char *buff = NULL;
	struct yall_subsystem *s = subsystems;

	yall_call_set_header(d, "Subsystems tree :");

	if (! s)
		return;

	do {
		curr_indent = (uint8_t)(curr_indent + indent);
		indent = 0;

		// Connectors are at most 10 char wide, so use this len.
		buff_size = 10U * (curr_indent + 1U) + strlen(s->name) + 1U;
		buff = calloc(buff_size, 1);

		for (uint8_t i = 0; i < curr_indent; ++i) {
			if (op[i] == connectors[VERTICAL_RIGHT])
				op[i] = connectors[VERTICAL];
			else if (op[i] == connectors[LIGHT_UP_RIGHT])
				op[i] = connectors[EMPTY];

			strncpy(&buff[strlen(buff)], op[i], strlen(op[i])+1);
		}

		if (s->next)
			op[curr_indent] = connectors[VERTICAL_RIGHT];
		else
			op[curr_indent] = connectors[LIGHT_UP_RIGHT];

		strncpy(&buff[strlen(buff)], op[curr_indent],
			strlen(op[curr_indent])+1);

		strncpy(&buff[strlen(buff)], s->name, strlen(s->name) + 1);

		yall_call_add_line(d, 0, buff);

		free(buff);
	} while ((s = get_next_subsystem(s, true, &indent)));
}

void yall_show_subsystems_tree(void)
{
	if (! yall_is_debug())
		return;

	_YALL_CALL_DBG_INFO(show_subsystems_tree_call, NULL);
}
