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

#include "yall_test.h"

#include <yall/yall.h>
#include <fcntl.h>

#ifdef __linux__
#include <semaphore.h>
#include <unistd.h>
#elif _WIN32
#include <Windows.h>
#include <io.h>

#define dup _dup
#define dup2 _dup2
#define fileno _fileno
#define open _open
#define close _close
#define O_RDWR _O_RDWR
#endif

struct yall_subsystem *subsystems;
struct yall_subsystem *_subsystems[_NB_TEST_SUBSYSTEMS] = { 0 };

TESTS_REDEFINE_LIGHT(snprintf)
int _tests_snprintf(char *str, size_t size, const char *format, ...)
{
	if (snprintf_fail)
		return -1;

	va_list args;
	va_start(args, format);

	return vsnprintf(str, size, format, args);
}

TESTS_REDEFINE_LIGHT(fprintf)
int _tests_fprintf(FILE *stream, const char *format, ...)
{
	if (fprintf_fail)
		return -1;

	va_list args;
	va_start(args, format);

	return vfprintf(stream, format, args);
}

TESTS_REDEFINE_LIGHT(malloc)
void *_tests_malloc(size_t size)
{
	if (malloc_fail)
		return NULL;

	return malloc(size);
}

TESTS_REDEFINE_LIGHT(fopen)
FILE *_tests_fopen(const char *pathname, const char *mode)
{
	if (fopen_fail)
		return NULL;
	
	return fopen(pathname, mode);
}

TESTS_REDEFINE(vsnprintf, -1, (char *str, size_t size, const char *format, va_list args), str, size, format, args)
TESTS_REDEFINE(strlen, -2, (const char *str), str)
TESTS_REDEFINE(pthread_create, -1, (pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg), thread, attr, start_routine, arg)

#ifdef __linux__
TESTS_REDEFINE(sem_wait, -1, (sem_t *sem), sem)
TESTS_REDEFINE(sem_init, -1, (sem_t *sem, int pshared, unsigned int value), sem, pshared, value)
#elif _WIN32
TESTS_REDEFINE_LIGHT(CreateMutex)
HANDLE _tests_CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName)
{
	if (CreateMutex_fail)
		return NULL;

	return CreateMutex(lpMutexAttributes, bInitialOwner, lpName);
}

TESTS_REDEFINE_LIGHT(WaitForSingleObject)
DWORD _tests_WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)
{
	if (WaitForSingleObject_fail)
		return 1;

	return WaitForSingleObject(hHandle, dwMilliseconds);
}
#endif

void test_init_yall(void)
{
	yall_init();
}

void test_close_yall(void)
{
	yall_close_all();
}

void test_create_json_config_file(void)
{
	FILE *f = fopen(_YALL_TEST_JSON_FILE, "a");
	fprintf(f, "{ }");
	fclose(f);
}

void test_remove_json_config_file(void)
{
	remove(_YALL_TEST_JSON_FILE);
}

void create_subsystems(void)
{
	yall_init();

	/* Subsystem 0 */
	_subsystems[0] = malloc(sizeof(struct yall_subsystem));
	subsystems = _subsystems[0];

	strcpy(_subsystems[0]->name, "0");

	_subsystems[0]->log_level = yall_debug;
	_subsystems[0]->output_type = yall_console_output;
	_subsystems[0]->file.filename = NULL;
	_subsystems[0]->status = yall_subsys_enable;
	_subsystems[0]->delete_old_log_file = true;
	_subsystems[0]->previous = NULL;
	_subsystems[0]->next = NULL;
	_subsystems[0]->parent = NULL;
	_subsystems[0]->childs = NULL;

	/* Subsystem 00 */
	_subsystems[4] = malloc(sizeof(struct yall_subsystem));
	subsystems->childs = _subsystems[4];

	strcpy(_subsystems[4]->name, "00");

	_subsystems[4]->log_level = yall_inherited_level;
	_subsystems[4]->output_type = yall_inherited_output;
	_subsystems[4]->file.filename = NULL;
	_subsystems[4]->status = yall_subsys_enable;
	_subsystems[4]->delete_old_log_file = true;
	_subsystems[4]->previous = NULL;
	_subsystems[4]->next = NULL;
	_subsystems[4]->parent = _subsystems[0];
	_subsystems[4]->childs = NULL;
	
	/* Subsystem 01*/
	_subsystems[5] = malloc(sizeof(struct yall_subsystem));
	subsystems->childs->next = _subsystems[5];

	strcpy(_subsystems[5]->name, "01");

	_subsystems[5]->log_level = yall_inherited_level;
	_subsystems[5]->output_type = yall_inherited_output;
	_subsystems[5]->file.filename = NULL;
	_subsystems[5]->status = yall_subsys_enable;
	_subsystems[5]->delete_old_log_file = true;
	_subsystems[5]->previous = _subsystems[4];
	_subsystems[5]->next = NULL;
	_subsystems[5]->parent = _subsystems[0];
	_subsystems[5]->childs = NULL;

	_subsystems[4]->next = _subsystems[5];

	/* Subsystem 02 */
	_subsystems[6] = malloc(sizeof(struct yall_subsystem));
	subsystems->childs->next->next = _subsystems[6];

	strcpy(_subsystems[6]->name, "02");

	_subsystems[6]->log_level = yall_warning;
	_subsystems[6]->output_type = yall_console_output;
	_subsystems[6]->file.filename = NULL;
	_subsystems[6]->status = yall_subsys_enable;
	_subsystems[6]->delete_old_log_file = true;
	_subsystems[6]->previous = _subsystems[5];
	_subsystems[6]->next = NULL;
	_subsystems[6]->parent = _subsystems[0];
	_subsystems[6]->childs = NULL;

	_subsystems[5]->next = _subsystems[6];

	/* Subsystem 1 */
	_subsystems[1] = malloc(sizeof(struct yall_subsystem));
	subsystems->next = _subsystems[1];

	strcpy(_subsystems[1]->name, "1");

	_subsystems[1]->log_level = yall_notice;
	_subsystems[1]->output_type = yall_console_output;
	_subsystems[1]->file.filename = NULL;
	_subsystems[1]->status = yall_subsys_enable;
	_subsystems[1]->delete_old_log_file = true;
	_subsystems[1]->previous = _subsystems[0];
	_subsystems[1]->next = NULL;
	_subsystems[1]->parent = NULL;
	_subsystems[1]->childs = NULL;

	_subsystems[0]->next = _subsystems[1];

	/* Subsystem 2 */
	_subsystems[2] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next = _subsystems[2];

	strcpy(_subsystems[2]->name, "2");

	_subsystems[2]->log_level = yall_warning;
	_subsystems[2]->output_type = yall_console_output;
	_subsystems[2]->file.filename = NULL;
	_subsystems[2]->status = yall_subsys_enable;
	_subsystems[2]->delete_old_log_file = true;
	_subsystems[2]->previous = _subsystems[1];
	_subsystems[2]->next = NULL;
	_subsystems[2]->parent = NULL;
	_subsystems[2]->childs = NULL;

	_subsystems[1]->next = _subsystems[2];

	/* Subsystem 20 */
	_subsystems[7] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->childs = _subsystems[7];

	strcpy(_subsystems[7]->name, "20");

	_subsystems[7]->log_level = yall_inherited_level;
	_subsystems[7]->output_type = yall_console_output;
	_subsystems[7]->file.filename = NULL;
	_subsystems[7]->status = yall_subsys_enable;
	_subsystems[7]->delete_old_log_file = true;
	_subsystems[7]->previous = NULL;
	_subsystems[7]->next = NULL;
	_subsystems[7]->parent = _subsystems[2];
	_subsystems[7]->childs = NULL;

	/* Subsystem 200 */
	_subsystems[8] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->childs->childs = _subsystems[8];

	strcpy(_subsystems[8]->name, "200");

	_subsystems[8]->log_level = yall_inherited_level;
	_subsystems[8]->output_type = yall_inherited_output;
	_subsystems[8]->file.filename = NULL;
	_subsystems[8]->status = yall_subsys_enable;
	_subsystems[8]->delete_old_log_file = true;
	_subsystems[8]->previous = NULL;
	_subsystems[8]->next = NULL;
	_subsystems[8]->parent = _subsystems[7];
	_subsystems[8]->childs = NULL;

	/* Subsystem 201 */
	_subsystems[9] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->childs->childs->next = _subsystems[9];

	strcpy(_subsystems[9]->name, "201");

	_subsystems[9]->log_level = yall_debug;
	_subsystems[9]->output_type = yall_inherited_output;
	_subsystems[9]->file.filename = strdup("output_file.log");
	_subsystems[9]->status = yall_subsys_enable;
	_subsystems[9]->delete_old_log_file = true;
	_subsystems[9]->previous = _subsystems[8];
	_subsystems[9]->next = NULL;
	_subsystems[9]->parent = _subsystems[7];
	_subsystems[9]->childs = NULL;

	_subsystems[8]->next = _subsystems[9];

	/* Subsystem 3 */
	_subsystems[3] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->next = _subsystems[3];

	strcpy(_subsystems[3]->name, "3");

	_subsystems[3]->log_level = yall_err;
	_subsystems[3]->output_type = yall_console_output;
	_subsystems[3]->file.filename = NULL;
	_subsystems[3]->status = yall_subsys_enable;
	_subsystems[3]->delete_old_log_file = true;
	_subsystems[3]->previous = _subsystems[2];
	_subsystems[3]->next = NULL;
	_subsystems[3]->parent = NULL;
	_subsystems[3]->childs = NULL;

	_subsystems[2]->next = _subsystems[3];

	/* Subsystem 4 */
	_subsystems[10] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->next->next = _subsystems[10];

	strcpy(_subsystems[10]->name, "4");

	_subsystems[10]->log_level = yall_debug;
	_subsystems[10]->output_type = yall_console_output;
	_subsystems[10]->file.filename = NULL;
	_subsystems[10]->status = yall_subsys_enable;
	_subsystems[10]->delete_old_log_file = true;
	_subsystems[10]->previous = _subsystems[3];
	_subsystems[10]->next = NULL;
	_subsystems[10]->parent = NULL;
	_subsystems[10]->childs = NULL;

	_subsystems[3]->next = _subsystems[10];

	/* Subsystem 40 */
	_subsystems[11] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->next->next->childs = _subsystems[11];

	strcpy(_subsystems[11]->name, "40");

	_subsystems[11]->log_level = yall_err;
	_subsystems[11]->output_type = yall_console_output;
	_subsystems[11]->file.filename = NULL;
	_subsystems[11]->status = yall_subsys_enable;
	_subsystems[11]->delete_old_log_file = true;
	_subsystems[11]->previous = NULL;
	_subsystems[11]->next = NULL;
	_subsystems[11]->parent = _subsystems[10];
	_subsystems[11]->childs = NULL;

	_subsystems[10]->childs = _subsystems[11];

	/* Subsystem 400 */
	_subsystems[12] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->next->next->childs->childs = _subsystems[12];

	strcpy(_subsystems[12]->name, "400");

	_subsystems[12]->log_level = yall_inherited_level;
	_subsystems[12]->output_type = yall_console_output;
	_subsystems[12]->file.filename = NULL;
	_subsystems[12]->status = yall_subsys_enable;
	_subsystems[12]->delete_old_log_file = true;
	_subsystems[12]->previous = NULL;
	_subsystems[12]->next = NULL;
	_subsystems[12]->parent = _subsystems[11];
	_subsystems[12]->childs = NULL;

	_subsystems[11]->childs = _subsystems[12];

	/* Subsystem 41 */
	_subsystems[13] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->next->next->childs->next = _subsystems[13];

	strcpy(_subsystems[13]->name, "41");

	_subsystems[13]->log_level = yall_inherited_level;
	_subsystems[13]->output_type = yall_console_output;
	_subsystems[13]->file.filename = NULL;
	_subsystems[13]->status = yall_inherited_status;
	_subsystems[13]->delete_old_log_file = true;
	_subsystems[13]->previous = _subsystems[11];
	_subsystems[13]->next = NULL;
	_subsystems[13]->parent = _subsystems[10];
	_subsystems[13]->childs = NULL;

	_subsystems[11]->next = _subsystems[13];

	/* Subsystem 410 */
	_subsystems[14] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->next->next->childs->next->childs = _subsystems[14];

	strcpy(_subsystems[14]->name, "410");

	_subsystems[14]->log_level = yall_inherited_level;
	_subsystems[14]->output_type = yall_console_output;
	_subsystems[14]->file.filename = NULL;
	_subsystems[14]->status = yall_subsys_enable;
	_subsystems[14]->delete_old_log_file = true;
	_subsystems[14]->previous = NULL;
	_subsystems[14]->next = NULL;
	_subsystems[14]->parent = _subsystems[13];
	_subsystems[14]->childs = NULL;

	_subsystems[13]->childs = _subsystems[14];

	/* Subsystem 5 */
	_subsystems[15] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->next->next->next = _subsystems[15];

	strcpy(_subsystems[15]->name, "5");

	_subsystems[15]->log_level = yall_debug;
	_subsystems[15]->output_type = yall_console_output;
	_subsystems[15]->file.filename = NULL;
	_subsystems[15]->status = yall_subsys_enable;
	_subsystems[15]->delete_old_log_file = true;
	_subsystems[15]->previous = _subsystems[10];
	_subsystems[15]->next = NULL;
	_subsystems[15]->parent = NULL;
	_subsystems[15]->childs = NULL;

	_subsystems[10]->next = _subsystems[15];
}

void clean_subsystems(void)
{
	for (int i = 0; i < _NB_TEST_SUBSYSTEMS; ++i) {
		if (_subsystems[i]) {
			free((void *)_subsystems[i]->file.filename);
			free(_subsystems[i]);
		}

		_subsystems[i] = NULL;
	}

	subsystems = NULL;

	yall_close_all();
}
