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
#include "yall/config/reader.h"

extern yall_error parse_config(json_t *config);

/*
 * Proper parameters
 */
Test(config_reader, test_parse_config0)
{
	cr_assert_eq(YALL_SUCCESS, parse_config(json_object()));
}

/*
 * NULL parameter
 */
Test(config_reader, test_parse_config1)
{
	cr_assert_eq(YALL_SUCCESS, parse_config(NULL));
}

/*
 * Invalid JSON object type
 */
Test(config_reader, test_parse_config2)
{
	cr_assert_eq(YALL_SUCCESS, parse_config(json_array()));
}

/*
 * Validate remain coverage line
 */
Test(config_reader, test_parse_config3)
{
	json_t *r = json_object();
	json_object_set(r, "testing", json_string("testing"));
	
	parse_config(r);
}