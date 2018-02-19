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

#include "helpers/h_subsystem.h"

#include <stdlib.h>
#include <string.h>
#include <yall/subsystem.h>

extern struct yall_subsystem *subsystems;
struct yall_subsystem *_subsystems[_NB_TEST_SUBSYSTEMS] = { 0 };

struct yall_subsystem *get_fake_subsystem(const char *name, const char *output_file)
{
        struct yall_subsystem *s = malloc(sizeof(struct yall_subsystem));
        s->parent = NULL;
        s->childs = NULL;
        s->previous = NULL;
        s->next = NULL;
        s->output_file = NULL;

        strcpy(s->name, name);

        if (output_file) {
                s->output_file = malloc(strlen(output_file) + 1);
                strcpy(s->output_file, output_file);
        }

        s->log_level = yall_debug;
        s->output_type = yall_console_output;

        s->status = yall_subsys_enable;
        s->delete_old_log_file = false;

        return s;
}

void free_fake_subsystem(struct yall_subsystem *s)
{
        free(s->output_file);
        free(s);
}

void create_subsystems(void)
{
        /* Subsystem 0 */
        _subsystems[0] = malloc(sizeof(struct yall_subsystem));
        subsystems = _subsystems[0];

        strcpy(_subsystems[0]->name, "0");

        _subsystems[0]->log_level = yall_debug;
        _subsystems[0]->output_type = yall_console_output;
        _subsystems[0]->output_file = NULL;
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
        _subsystems[4]->output_file = NULL;
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
        _subsystems[5]->output_file = NULL;
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
        _subsystems[6]->output_file = NULL;
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
        _subsystems[1]->output_file = NULL;
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
        _subsystems[2]->output_file = NULL;
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
        _subsystems[7]->output_file = NULL;
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
        _subsystems[8]->output_file = NULL;
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
        _subsystems[9]->output_file = NULL;
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
        _subsystems[3]->output_file = NULL;
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
        _subsystems[10]->output_file = NULL;
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
        _subsystems[11]->output_file = NULL;
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
        _subsystems[12]->output_file = NULL;
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
        _subsystems[13]->output_file = NULL;
        _subsystems[13]->status = yall_subsys_enable;
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
        _subsystems[14]->output_file = NULL;
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
        _subsystems[15]->output_file = NULL;
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
                if (_subsystems[i])
                        free(_subsystems[i]);

                _subsystems[i] = NULL;
        }

        subsystems = NULL;
}
