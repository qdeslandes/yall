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

#ifndef _TESTS_HELPERS_SUBSYSTEMS_H
#define _TESTS_HELPERS_SUBSYSTEMS_H

#include "yall/subsystem.h"

#define _NB_TEST_SUBSYSTEMS 16

/*
 * As this structure is defined inside a .c file, we need to redefine it here
 * to allow testing its content.
 */
struct yall_subsystem {
	char name[SUBSYS_NAME_LEN];
	enum yall_log_level log_level;
#ifdef __linux__
	_Atomic enum yall_subsys_status status;
#elif _WIN32
	enum yall_subsys_status status;
#endif
	enum yall_output_type output_type;
	char *output_file;
	bool delete_old_log_file;
	struct yall_subsystem *parent;
	struct yall_subsystem *childs;
	struct yall_subsystem *previous;
	struct yall_subsystem *next;
};

extern struct yall_subsystem *_subsystems[_NB_TEST_SUBSYSTEMS];

struct yall_subsystem *get_fake_subsystem(const char *name, const char *output_file);
void free_fake_subsystem(struct yall_subsystem *s);
void create_subsystems(void);
void clean_subsystems(void);

#endif
