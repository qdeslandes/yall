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

#include "yall/config/reader.h"

#include <stdio.h>
#include <jansson.h>
#include <string.h>

#include "yall/debug.h"

/**
 * \brief From a parameter key and its value, this function set up the proper
 *	library's parameter configuration. This isn't the best way we could
 *	achieve this, but there is only 3 different parameters to set, so it
 *	could be sufficient for the moment. Once we have more parameters to
 *	manage, this behaviour could be improved.
 * \param key Key defining the parameter
 * \param value Value of the parameter to set, as a json_t type, it has to be
 *	converted to the proper type.
 */
static void set_json_config(const char *key, json_t *value)
{
	/*
	 * Using a bunch of if is not a problem for the moment, as there is only
	 * 3 parameters the configuration can modify. But a better way to
	 * implement this should be found as soon as more parameters are
	 * defined.
	 */
	if (strcmp("std_header_template", key) == 0 && json_is_string(value))
		yall_config_set_std_header_template(json_string_value(value));
	else if (strcmp("call_header_template", key) == 0 &&
		json_is_string(value))
		yall_config_set_call_header_template(json_string_value(value));
	else if (strcmp("tab_width", key) == 0 && json_is_integer(value))
		yall_config_set_tab_width((uint8_t)json_integer_value(value));
	else
		_YALL_DBG_WARNING("Parameter key or type invalid for \"%s\"",
			key);
}

/**
 * \brief Parse the given JSON object to retrieve subsystems from it. It loops
 *	on the JSON object available in the given paremeter and apply them
 *	depending of their name. See the documentation for informations about
 *	how to manage library parameters in configuration file.
 * \param config Root JSON object containing the library configuration.
 * \return Error code depending the result of the function. If there is not
 *	config parameters, this is not an error, as the user can choose to not
 *	define it.
 */
static yall_error parse_config(json_t *config)
{
	const char *key = NULL;
	json_t *value = NULL;

	if (! config || ! json_is_object(config))
		goto end;

	json_object_foreach(config, key, value) {
		set_json_config(key, value);
	}

end:
	return YALL_SUCCESS;
}

/**
 * \brief Parse the given JSON object to retrieve subsystems from it. It get the
 *	subsystem (JSON object) named as in the second parameter. Then, it check
 *	if this subsystem has a parent, if it does, call itself with the name of
 *	the parent as second parameter, untile their is no parent requested. See
 *	the documentation for informations about how to define a subsystem in
 *	configuration file.
 *	/!\ TODO : what if there is a recursive dependency ?
 * \param subsystems Root subsystems object of the JSON data.
 * \param subsystem_str Subsystem to start from.
 * \return Error code depending the result of the function.
 */
static yall_error parse_subsystems(json_t *subsystems,
	const char *subsystem_str)
{
	json_t *s = NULL;
	json_t *parent = NULL;
	yall_error ret = YALL_SUCCESS;
	const char *parent_str = NULL;
	const char *yall_log_level = NULL;
	const char *yall_output_type = NULL;

	s = json_object_get(subsystems, subsystem_str);
	if (! s) {
		_YALL_DBG_WARNING(
			"JSON: Referencing undeclared subsystem \"%s\".",
			subsystem_str);
		ret = YALL_JSON_UNDECLARED_SUBSYS;
		goto end;
	}

	if (json_object_get(s, "yall_checked_object"))
		return YALL_JSON_CIRCLE_DEPENDENCY;
	json_object_set_new(s, "yall_checked_object", json_object());

	parent = json_object_get(s, "parent");
	if (parent) {
		parent_str = json_string_value(parent);

		if(! get_subsystem(parent_str, NULL)) {
			ret = parse_subsystems(subsystems, parent_str);
			if (ret == YALL_JSON_CIRCLE_DEPENDENCY) {
				_YALL_DBG_WARNING(
					"JSON: Circle dependency detected.");
				parent_str = NULL;
			} else if (ret != YALL_SUCCESS) {
				goto end;
			}
		}
	}

	/*
	 * If the key is not found, NULL is returned from json_object_get,
	 * json_string_value then returns NULL too, as the input isn't a valid
	 * json_t object.
	 */
	yall_log_level = json_string_value(json_object_get(s, "log_level"));
	yall_output_type = json_string_value(json_object_get(s, "output_type"));

	ret = yall_set_subsystem(subsystem_str, parent_str,
		str_to_log_level(yall_log_level),
		str_to_output_type(yall_output_type),
		json_string_value(json_object_get(s, "output_file")));

end:
	return ret;
}

/**
 * \brief From the given root JSON parameter, it parse the tree to extract the
 *	different yall parameters.
 * \param root Root of the JSON configuration tree.
 * \return Error code depending the result of the function.
 */
static yall_error parse_json_config(json_t *root)
{
	void *tmp = NULL;
	json_t *value = NULL;
	const char *key = NULL;
	json_t *subsystems = NULL;
	yall_error ret = YALL_SUCCESS;

	parse_config(json_object_get(root, "config"));

	/*
	 * json_object_foreach_safe allow use to use json_object_del on each
	 * subsystem found.
	 * If there is not subsystem object found in JSON data, foreach does not
	 * process and returns.
	 */
	subsystems = json_object_get(root, "subsystems");
	json_object_foreach_safe(subsystems, tmp, key, value) {
		ret = parse_subsystems(subsystems, key);
		if (ret != YALL_SUCCESS)
			goto end;
	}

end:
	return ret;
}

yall_error read_config(const char *filename)
{
	yall_error ret = YALL_SUCCESS;
	json_error_t json_err;
	json_t *root = NULL;

	root = json_load_file(filename, 0, &json_err);
	if (! root) {
		_YALL_DBG_ERR("Can't read configuration : %s.", json_err.text);
		ret = YALL_JSON_CANT_READ_CONFIG;
		goto end;
	}

	parse_json_config(root);

	// Manually decref references of root object to ensure it is destroyed.
	json_decref(root);

end:
	return ret;
}
