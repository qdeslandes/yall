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

#include "subsystem/test.h"

static void tests_subsystem_setup(void)
{
	cr_redirect_stderr();
}

static void tests_subsystem_clean(void)
{

}

TestSuite(subsystem, .init=tests_subsystem_setup, .fini=tests_subsystem_clean);

struct yall_subsystem *get_fake_subsystem(const char *name, const char *output_file)
{
	struct yall_subsystem *s = malloc(sizeof(struct yall_subsystem));
	s->parent = NULL;
	s->childs = NULL;
	s->previous = NULL;
	s->next = NULL;
	s->file.filename = NULL;

	strcpy(s->name, name);

	if (output_file)
		s->file.filename = strdup(output_file);

	s->log_level = yall_debug;
	s->output_type = yall_console_output;

	s->status = yall_subsys_enable;
	s->delete_old_log_file = false;

	return s;
}

void free_fake_subsystem(struct yall_subsystem *s)
{
	free((char *)s->file.filename);
	free(s);
}
