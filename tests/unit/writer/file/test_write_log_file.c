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

#include "writer/file/test.h"

/*
 * O.K.
 */
Test(writer_file, test_write_log_file0, .fini=test_clean_delete_log_file)
{
	cr_assert_eq(YALL_SUCCESS, write_log_file(_YALL_TEST_LOG_FILE, "yall"));
}

/*
 * O.K.
 * NULL message
 */
Test(writer_file, test_write_log_file1, .fini=test_clean_delete_log_file)
{
	cr_assert_eq(YALL_SUCCESS, write_log_file(_YALL_TEST_LOG_FILE, NULL));
}

/*
 * fopen fail
 */
Test(writer_file, test_write_log_file2, .fini=test_clean_delete_log_file)
{
	disable_fopen();
	cr_assert_eq(YALL_FILE_OPEN_ERR, write_log_file(_YALL_TEST_LOG_FILE, "yall"));
	enable_fopen();
}
