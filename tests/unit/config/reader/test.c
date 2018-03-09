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

#include "config/reader/test.h"

json_t *json_subsys_root = NULL;

static void tests_config_reader_setup(void)
{

}

static void tests_config_reader_clean(void)
{

}

TestSuite(config_reader, .init=tests_config_reader_setup, .fini=tests_config_reader_clean);

void test_init_with_json_subsystems(void)
{
	yall_init();

	json_subsys_root = json_object();
	
	/*
	 * "root" : {
	 *	"log_level" : "yall_debug",
	 *	"output_type" : "yall_console_output"
	 * }
	 */
	json_t *root = json_object();
	json_object_set(root, "log_level", json_string("yall_debug"));
	json_object_set(root, "output_type", json_string("yall_console_output"));
	json_object_set(json_subsys_root, "root", root);

	/*
	 * "first_child" : {
	 *	"parent" : "root",
	 *	"log_level" : "yall_inherited_level",
	 *	"output_type" : "yall_console_output"
	 * }
	 */
	json_t *first_child = json_object();
	json_object_set(first_child, "parent", json_string("root"));
	json_object_set(first_child, "log_level", json_string("yall_inherited_level"));
	json_object_set(first_child, "output_type", json_string("yall_console_output"));
	json_object_set(json_subsys_root, "first_child", first_child);

	/*
	 * "second_child" : {
	 *	"parent" : "root",
	 *	"log_level" : "yall_info",
	 *	"output_type" : "yall_inherited_output"
	 * }
	 */
	json_t *second_child = json_object();
	json_object_set(second_child, "parent", json_string("root"));
	json_object_set(second_child, "log_level", json_string("yall_info"));
	json_object_set(second_child, "output_type", json_string("yall_inherited_output"));
	json_object_set(json_subsys_root, "second_child", second_child);

	/*
	 * "second_root" : {
	 *	"log_level" : "yall_info",
	 *	"output_type" : "yall_inherited_output"
	 * }
	 */
	json_t *second_root = json_object();
	json_object_set(second_root, "log_level", json_string("yall_info"));
	json_object_set(second_root, "output_type", json_string("yall_inherited_output"));
	json_object_set(json_subsys_root, "second_root", second_root);

	/*
	 * "third_child" : {
	 *	"parent" : "second_root",
	 *	"log_level" : "yall_inherited_level",
	 *	"output_type" : "yall_inherited_output"
	 * }
	 */
	json_t *third_child = json_object();
	json_object_set(third_child, "parent", json_string("second_root"));
	json_object_set(third_child, "log_level", json_string("yall_inherited_level"));
	json_object_set(third_child, "output_type", json_string("yall_inherited_output"));
	json_object_set(json_subsys_root, "third_child", third_child);

	/*
	 * "fourth_child" : {
	 *	"parent" : "second_root",
	 *	"log_level" : "yall_debug",
	 *	"output_type" : "yall_console_output"
	 * }
	 */
	json_t *fourth_child = json_object();
	json_object_set(fourth_child, "parent", json_string("second_root"));
	json_object_set(fourth_child, "log_level", json_string("yall_debug"));
	json_object_set(fourth_child, "output_type", json_string("yall_console_output"));
	json_object_set(json_subsys_root, "fourth_child", fourth_child);
}
