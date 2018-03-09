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

#ifndef _TEST_SUBSYSTEM_H
#define _TEST_SUBSYSTEM_H

#include "yall_test.h"

#include <stdbool.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/theories.h>
#include <jansson.h>

#include "yall/subsystem.h"
#include "yall/call.h"
#include "yall/debug.h"
#include "yall/utils.h"

extern void _free_subsystem(struct yall_subsystem *s);
extern struct yall_subsystem *_get_subsystem(const char *name,
	struct yall_subsystem *s, struct yall_subsystem_params *params);
extern struct yall_subsystem *get_next_subsystem(struct yall_subsystem *s,
	bool crawl_childs, int8_t *d);
extern void set_default_params(struct yall_subsystem_params *params);
extern void show_subsystems_tree_call(struct yall_call_data *d, const void *args);
extern void set_subsys_status(const char *subsys_name, enum yall_subsys_status status);
extern void reset_subsystem(struct yall_subsystem *s);

struct yall_subsystem *get_fake_subsystem(const char *name, const char *output_file);
void free_fake_subsystem(struct yall_subsystem *s);

#endif
