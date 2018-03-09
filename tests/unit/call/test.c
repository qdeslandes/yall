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

#include "call/test.h"

static void test_call_setup(void)
{

}

static void test_call_clean(void)
{

}

TestSuite(call, .init=test_call_setup, .fini=test_call_clean);

const char *test_header = NULL;
struct yall_call_data test_call_data = { 0 };
struct yall_call_data_line *test_call_data_lines_array[2] = { 0 };

void test_2_call_data_lines(void)
{
	test_call_data.header = strdup("yall");
	add_line(&test_call_data, strdup("data"));
	add_line(&test_call_data, strdup("test"));

	test_header = test_call_data.header;
	test_call_data_lines_array[0] = test_call_data.lines;
	test_call_data_lines_array[1] = test_call_data.lines->next;
}

void test_clean_2_call_data_lines(void)
{
	free((void *)test_header);

	free(test_call_data_lines_array[0]->content);
	free(test_call_data_lines_array[0]);

	free(test_call_data_lines_array[1]->content);
	free(test_call_data_lines_array[1]);
}
