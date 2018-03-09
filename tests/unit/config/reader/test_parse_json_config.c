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


/*
 * O.K.
 * yall_set_subsystem() is called, so the library must be initialized.
 */
Test(config_reader, test_parse_json_config0, .init=test_yall_init, .fini=test_yall_close)
{
	json_t *root = json_object();
	json_t *subsys = json_object();
	json_t *subsys_root = json_object();

	json_object_set(subsys, "root", subsys_root);
	json_object_set(root, "subsystems", subsys);

	cr_assert_eq(YALL_SUCCESS, parse_json_config(root));
}

/*
 * O.K.
 * NULL JSON parameter
 */
Test(config_reader, test_parse_json_config1)
{
	cr_assert_eq(YALL_SUCCESS, parse_json_config(NULL));
}

/*
 * Undeclared subsystem
 */
Test(config_reader, test_parse_json_config2)
{
	json_t *root = json_object();
	json_t *subsys = json_object();
	json_t *subsys_root = json_object();
	json_object_set(subsys_root, "parent", json_string("invalid"));
	json_object_set(subsys, "root", subsys_root);
	json_object_set(root, "subsystems", subsys);

	cr_assert_eq(YALL_JSON_UNDECLARED_SUBSYS, parse_json_config(root));
}
