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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/file.h"

#include <stdio.h>

#ifdef __linux__
#       include <semaphore.h>
#elif _WIN32
#       include <Windows.h>
#endif

#include "yall/utils.h"
#include "yall/errors.h"
#include "yall/debug.h"

#ifdef __linux__
extern sem_t file_sem;
#elif _WIN32
extern HANDLE file_sem;
#endif

uint8_t write_log_file(const char *file, const char *msg)
{
        uint32_t sem_ret = 0;
        uint8_t ret = YALL_OK;

#ifdef __linux__
        sem_ret = sem_wait(&file_sem);
#elif _WIN32
        sem_ret = WaitForSingleObject(file_sem, INFINITE);
#endif

        if (sem_ret != 0) {
                ret = YALL_FILE_LOCK_ERR;
                goto end;
        }

        FILE *f = fopen(file, "a");

        if (f) {
                fprintf(f, "%s", msg);
                fclose(f);
        } else {
                ret = YALL_FILE_OPEN_ERR;
        }

#ifdef __linux__
        sem_post(&file_sem);
#elif _WIN32
        ReleaseMutex(file_sem);
#endif

end:
        return ret;
}

void delete_old_log_file(const char *filepath)
{
        remove(filepath);
}
