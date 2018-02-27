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

#include "config/test_config.h"

#include <jansson.h>

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

extern json_t *subsys_root;
extern struct yall_subsystem *subsystems;
extern yall_error parse_subsystems(json_t *subsystems, const char *subsystem_str);

/*
 * Calling with undeclared subsystem
 */
Test(config_reader, test_parse_subsystems0, .init=test_config_json_subsystems_init, .fini=test_config_json_subsystems_clean)
{
	cr_assert_eq(YALL_JSON_UNDECLARED_SUBSYS, parse_subsystems(subsys_root, "invalid"));
}

/*
 * Circle dependencies between subsystems
 */
Test(config_reader, test_parse_subsystems1, .init=test_config_json_subsystems_init, .fini=test_config_json_subsystems_clean)
{
	yall_init();

	json_t *r = json_object();
	json_t *a = json_object();
	json_object_set(a, "parent", json_string("b"));
	json_t *b = json_object();
	json_object_set(b, "parent", json_string("a"));
	json_object_set(r, "a", a);
	json_object_set(r, "b", b);

	cr_assert_eq(YALL_SUCCESS, parse_subsystems(r, "a"));

	yall_close_all();
}

/*
 * Everyting is OK
 */
Test(config_reader, test_parse_subsystems2, .init=test_config_json_subsystems_init, .fini=test_config_json_subsystems_clean)
{
	parse_subsystems(subsys_root, "root");
	parse_subsystems(subsys_root, "first_child");
	parse_subsystems(subsys_root, "second_child");
	parse_subsystems(subsys_root, "second_root");
	parse_subsystems(subsys_root, "third_child");
	parse_subsystems(subsys_root, "fourth_child");

	struct yall_subsystem *root = subsystems;
	struct yall_subsystem *first_child = root->childs;
	struct yall_subsystem *second_child = first_child->next;
	struct yall_subsystem *second_root = subsystems->next;
	struct yall_subsystem *third_child = second_root->childs;
	struct yall_subsystem *fourth_child = third_child->next;

	cr_assert_eq(root->parent, NULL);
	cr_assert_eq(root->log_level, yall_debug);
	cr_assert_eq(root->output_type, yall_console_output);
	cr_assert_eq(root->output_file, NULL);
	cr_assert_str_eq(root->name, "root");

	cr_assert_eq(first_child->parent, root);;
	cr_assert_eq(first_child->log_level, yall_inherited_level);
	cr_assert_eq(first_child->output_type, yall_console_output);
	cr_assert_eq(first_child->output_file, NULL);
	cr_assert_str_eq(first_child->name, "first_child");

	parse_subsystems(subsys_root, "second_child");
	cr_assert_eq(second_child->parent, root);
	cr_assert_eq(second_child->log_level, yall_info);
	cr_assert_eq(second_child->output_type, yall_inherited_output);
	cr_assert_eq(second_child->output_file, NULL);
	cr_assert_str_eq(second_child->name, "second_child");

	cr_assert_eq(second_root->parent, NULL);
	cr_assert_eq(second_root->log_level, yall_info);
	cr_assert_eq(second_root->output_type, yall_inherited_output);
	cr_assert_eq(second_root->output_file, NULL);
	cr_assert_str_eq(second_root->name, "second_root");

	cr_assert_eq(third_child->parent, second_root);
	cr_assert_eq(third_child->log_level, yall_inherited_level);
	cr_assert_eq(third_child->output_type, yall_inherited_output);
	cr_assert_eq(third_child->output_file, NULL);
	cr_assert_str_eq(third_child->name, "third_child");

	cr_assert_eq(fourth_child->parent, second_root);
	cr_assert_eq(fourth_child->log_level, yall_debug);
	cr_assert_eq(fourth_child->output_type, yall_console_output);
	cr_assert_eq(fourth_child->output_file, NULL);
	cr_assert_str_eq(fourth_child->name, "fourth_child");
}