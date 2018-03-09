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
 */
Test(config_reader, test_parse_config0)
{
	cr_assert_eq(YALL_SUCCESS, parse_config(json_object()));
}

/*
 * O.K. with JSON content
 */
Test(config_reader, test_parse_config1)
{
	json_t *r = json_object();
	json_object_set(r, "azerty", json_string("azerty"));
	
	cr_assert_eq(YALL_SUCCESS, parse_config(r));
}

/*
 * NULL parameter
 */
Test(config_reader, test_parse_config2)
{
	cr_assert_eq(YALL_SUCCESS, parse_config(NULL));
}

/*
 * Parameter is not a JSON object
 */
Test(config_reader, test_parse_config3)
{
	cr_assert_eq(YALL_SUCCESS, parse_config(json_array()));
}
