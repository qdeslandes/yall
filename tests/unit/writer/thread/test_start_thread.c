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

#include "writer/thread/test.h"

/*
 * O.K.
 */
Test(writer_thread, test_start_thread0, .fini=test_stop_thread)
{
	cr_assert_eq(YALL_SUCCESS, start_thread(60));
}

/*
 * O.K.
 * Do not use standard frequency
 */
Test(writer_thread, test_start_thread1, .fini=test_stop_thread)
{
	cr_assert_eq(YALL_SUCCESS, start_thread(260));
}

/*
 * Thread creation fail
 */
Test(writer_thread, test_start_thread2)
{
	disable_pthread_create();
	cr_assert_eq(YALL_CANT_CREATE_THREAD, start_thread(60));
	enable_pthread_create();
}
