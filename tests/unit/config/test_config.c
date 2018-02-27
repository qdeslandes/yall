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

#include "test_config.h"

#include <jansson.h>

extern struct yall_config default_config;
extern struct yall_config current_config;

json_t *subsys_root = NULL;

static void tests_config_setup(void)
{
}

static void tests_config_clean(void)
{

}

TestSuite(config, .init=tests_config_setup, .fini=tests_config_clean);

void test_config_config_setup(void)
{
    config_setup();
}

void test_config_config_clean(void)
{
    config_clean();
}

void test_config_setup_clean(void)
{
    config_clean();
}

void test_config_clean_setup(void)
{
    config_setup();
}

void test_config_json_subsystems_init(void)
{
	yall_close_all();
	yall_init();

	subsys_root = json_object();
	
	json_t *root = json_object();
	json_object_set(root, "log_level", json_string("yall_debug"));
	json_object_set(root, "output_type", json_string("yall_console_output"));

	json_t *first_child = json_object();
	json_object_set(first_child, "parent", json_string("root"));
	json_object_set(first_child, "log_level", json_string("yall_inherited_level"));
	json_object_set(first_child, "output_type", json_string("yall_console_output"));

	json_t *second_child = json_object();
	json_object_set(second_child, "parent", json_string("root"));
	json_object_set(second_child, "log_level", json_string("yall_info"));
	json_object_set(second_child, "output_type", json_string("yall_inherited_output"));

	json_t *second_root = json_object();
	json_object_set(second_root, "log_level", json_string("yall_info"));
	json_object_set(second_root, "output_type", json_string("yall_inherited_output"));

	json_t *third_child = json_object();
	json_object_set(third_child, "parent", json_string("second_root"));
	json_object_set(third_child, "log_level", json_string("yall_inherited_level"));
	json_object_set(third_child, "output_type", json_string("yall_inherited_output"));

	json_t *fourth_child = json_object();
	json_object_set(fourth_child, "parent", json_string("second_root"));
	json_object_set(fourth_child, "log_level", json_string("yall_debug"));
	json_object_set(fourth_child, "output_type", json_string("yall_console_output"));

	json_object_set(subsys_root, "root", root);
	json_object_set(subsys_root, "first_child", first_child);
	json_object_set(subsys_root, "second_child", second_child);
	json_object_set(subsys_root, "second_root", second_root);
	json_object_set(subsys_root, "third_child", third_child);
	json_object_set(subsys_root, "fourth_child", fourth_child);
}

void test_config_json_subsystems_clean(void)
{
	yall_close_all();
}