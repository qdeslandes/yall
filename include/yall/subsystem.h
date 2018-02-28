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

#ifndef _YALL_SUBSYSTEM_H
#define _YALL_SUBSYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#include "yall/utils.h"
#include "yall/status.h"
#include "yall/log_level.h"
#include "yall/output/types.h"

#define SUBSYS_NAME_LEN	 16

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
 * \var yall_subsystem::console
 *	\brief Store the console's output type configuration.
 * \var yall_subsystem::file
 *	\brief Store the file's output type configuration.
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
	enum yall_subsys_status status;
	enum yall_output_type output_type;
	bool delete_old_log_file;
	/* Configuration */
	struct yall_console_output_config console;
	struct yall_file_output_config file;
	/* Node data */
	struct yall_subsystem *parent;
	struct yall_subsystem *childs;
	struct yall_subsystem *previous;
	struct yall_subsystem *next;
};

/**
 * \struct yall_subsystem_params
 * \brief This structure is used as a placeholder for parameter during the
 *	processing of a log message. It is not possible to directly use the
 *	struct yall_subsystem parameters as it could contains inherited values.
 * \var yall_subsystem::log_level
 *	\brief Log level to use with the requested subsystem.
 * \var yall_subsystem::status
 *	\brief Current status of the requested subsystem.
 * \var yall_subsystem::output_type
 *	\brief Output type for the requested subsystem.
 * \var yall_subsystem::console
 *	\brief Console output type parameters.
 * \var yall_subsystem::file
 *	\brief File output type parameters.
 */
struct yall_subsystem_params {
	enum yall_log_level log_level;
	enum yall_subsys_status status;
	enum yall_output_type output_type;
	struct yall_console_output_config console;
	struct yall_file_output_config file;
};

/**
 * \brief Disable a given subsystem. Once disabled, the subsystem can't emit
 *	log messages anymore.
 *	This function is not thread safe.
 * \param subsys_name Name of the subsystem to disable. Can't be NULL.
 */
_YALL_PUBLIC void yall_disable_subsystem(const char *subsys_name);

/**
 * \brief Enable a given filesystem.
 *	This function is not thread safe.
 * \param subsys_name Name of the subsystem to enable. Can't be NULL.
 */
_YALL_PUBLIC void yall_enable_subsystem(const char *subsys_name);

/**
 * \brief If a subsystem of the given *name* is available,
 *      returns it. If not, the function returns NULL.
 * \param name Name of the subsystem to return. Can't be NULL.
 * \param params Structure holding the researched subsystem's parameters,
 *	replacing replacing inherited values with correct ones. If this
 *	parameters is NULL, subsystems parameters are not retrieved. If a
 *	parameter is missing, the default one is used.
 * \return The requested subsystem.
 */
struct yall_subsystem *get_subsystem(const char *name,
	struct yall_subsystem_params *params);

/**
 * \brief Create a new subsystem with the given parameters and returns it. This
 *	function can't fail. It is better to use this function instead of
 *	manually crafting the subsystem as it set some pointers used for tree
 *	crawling, which should have a specific value.
 * \param name Name of the created subsystem. Can't be NULL.
 * \param log_level Minimum log level for the created subsystem.
 * \param output_type Output type for the created subsystem. See
 *	enum yall_output_type for more.
 * \param output_file Output file to write logs for the created subsystem, if
 *	output_type is yall_file_output, can be NULL otherwise.
 * \return The newly created subsystem.
 */
struct yall_subsystem *create_subsystem(const char *name,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file);

/**
 * \brief Add the given subsystem to the subsystem's tree. Handle inheritance.
 *	If parent is NULL or not found, the subsystem will be added to the
 *	top-level tree. No subsystem with the new subsystem's name should be
 *	present in the tree.
 * \param parent Name of the parent subsystem if any or NULL.
 * \param s Subsystem to add to the tree; Can't be NULL.
 */
void add_subsystem(const char *parent, struct yall_subsystem *s);

/**
 * \brief Update a given subsystem : from an existing subsystem it upadte its
 *	parameters instead of creating a new one.
 * \param s The subsystem to update.
 * \param log_level New log level of the subsystem.
 * \param output_type New output type of the subsystem.
 * \param output_file New output file of the subsystem.
 */
void update_subsystem(struct yall_subsystem *s,
	enum yall_log_level log_level,
	enum yall_output_type output_type,
	const char *output_file);

/**
 * \brief Remove a subsystem for the subsystems tree, it does not delete it. If
 *	this subsystem has childs, the childs will be removed too.
 * \param name Name of the subsystem to remove from the tree.
 * \return The requested subsystem if found, NULL otherwise.
 */
struct yall_subsystem *remove_subsystem(const char *name);

/**
 * \brief Free the given subsystems list with _free_subsystem().
 * \param s The list of subsystem to free. It will be used as the root of the
 *	tree, so its parents won't be freed.
 */
void _free_subsystems(struct yall_subsystem *s);

/**
 * \brief Free the library's subsystems list.
 */
void free_subsystems(void);

/**
 * \brief Display the subsystems tree. Supports up to 32
 *	nested subsystems. This function is not thread safe.
 * \remark This function can only be called when debug mode is activated.
 */
_YALL_PUBLIC void yall_show_subsystems_tree(void);

#endif
