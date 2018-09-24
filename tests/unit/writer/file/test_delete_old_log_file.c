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
Test(writer_file, test_delete_old_log_file0, .init=test_init_create_old_log_file, .fini=test_clean_delete_old_log_file)
{
	delete_old_log_file(_YALL_TEST_OLD_LOG_FILE);
	cr_assert(1);
}

/*
 * O.K.
 * NULL file name
 * Useful if suddenly with function would fail on a NULL parameter.
 */
Test(writer_file, test_delete_old_log_file1, .init=test_init_create_old_log_file, .fini=test_clean_delete_old_log_file)
{
	delete_old_log_file(NULL);
	cr_assert(1);
}