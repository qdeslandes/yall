#include "h_subsystem.h"
#include <stdlib.h>
#include <string.h>
#include <yall/subsystem.h>

struct yall_subsystem *_subsystems[10] = { 0 };

void create_subsystems(void)
{
	extern struct yall_subsystem *subsystems;

	/* Subsystem 0 */
	_subsystems[0] = malloc(sizeof(struct yall_subsystem));
	subsystems = _subsystems[0];

	_subsystems[0]->name = malloc(sizeof("0")+1);
	strcpy(_subsystems[0]->name, "0");

	_subsystems[0]->log_level = yall_debug;
	_subsystems[0]->output_type = yall_console_output;
	_subsystems[0]->previous = NULL;
	_subsystems[0]->next = NULL;
	_subsystems[0]->parent = NULL;
	_subsystems[0]->childs = NULL;

	/* Subsystem 00 */
	_subsystems[4] = malloc(sizeof(struct yall_subsystem));
	subsystems->childs = _subsystems[4];

	_subsystems[4]->name = malloc(sizeof("00")+1);
	strcpy(_subsystems[4]->name, "00");

	_subsystems[4]->log_level = yall_inherited_level;
	_subsystems[4]->output_type = yall_inherited_output;
	_subsystems[4]->previous = NULL;
	_subsystems[4]->next = NULL;
	_subsystems[4]->parent = _subsystems[0];
	_subsystems[4]->childs = NULL;

	/* Subsystem 01*/
	_subsystems[5] = malloc(sizeof(struct yall_subsystem));
	subsystems->childs->next = _subsystems[5];

	_subsystems[5]->name = malloc(sizeof("01")+1);
	strcpy(_subsystems[5]->name, "01");

	_subsystems[5]->log_level = yall_inherited_level;
	_subsystems[5]->output_type = yall_inherited_output;
	_subsystems[5]->previous = _subsystems[4];
	_subsystems[5]->next = NULL;
	_subsystems[5]->parent = _subsystems[0];
	_subsystems[5]->childs = NULL;

	_subsystems[4]->next = _subsystems[5];

	/* Subsystem 02 */
	_subsystems[6] = malloc(sizeof(struct yall_subsystem));
	subsystems->childs->next->next = _subsystems[6];

	_subsystems[6]->name = malloc(sizeof("02")+1);
	strcpy(_subsystems[6]->name, "02");

	_subsystems[6]->log_level = yall_warning;
	_subsystems[6]->output_type = yall_console_output;
	_subsystems[6]->previous = _subsystems[5];
	_subsystems[6]->next = NULL;
	_subsystems[6]->parent = _subsystems[0];
	_subsystems[6]->childs = NULL;

	_subsystems[5]->next = _subsystems[6];

	/* Subsystem 1 */
	_subsystems[1] = malloc(sizeof(struct yall_subsystem));
	subsystems->next = _subsystems[1];

	_subsystems[1]->name = malloc(sizeof("1")+1);
	strcpy(_subsystems[1]->name, "1");

	_subsystems[1]->log_level = yall_notice;
	_subsystems[1]->output_type = yall_console_output;
	_subsystems[1]->previous = _subsystems[0];
	_subsystems[1]->next = NULL;
	_subsystems[1]->parent = NULL;
	_subsystems[1]->childs = NULL;

	_subsystems[0]->next = _subsystems[1];

	/* Subsystem 2 */
	_subsystems[2] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next = _subsystems[2];

	_subsystems[2]->name = malloc(sizeof("2")+1);
	strcpy(_subsystems[2]->name, "2");

	_subsystems[2]->log_level = yall_warning;
	_subsystems[2]->output_type = yall_console_output;
	_subsystems[2]->previous = _subsystems[1];
	_subsystems[2]->next = NULL;
	_subsystems[2]->parent = NULL;
	_subsystems[2]->childs = NULL;

	_subsystems[1]->next = _subsystems[2];

	/* Subsystem 20 */
	_subsystems[7] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->childs = _subsystems[7];

	_subsystems[7]->name = malloc(sizeof("20")+1);
	strcpy(_subsystems[7]->name, "20");

	_subsystems[7]->log_level = yall_inherited_level;
	_subsystems[7]->output_type = yall_console_output;
	_subsystems[7]->previous = NULL;
	_subsystems[7]->next = NULL;
	_subsystems[7]->parent = _subsystems[2];
	_subsystems[7]->childs = NULL;

	/* Subsystem 200 */
	_subsystems[8] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->childs->childs = _subsystems[8];

	_subsystems[8]->name = malloc(sizeof("200")+1);
	strcpy(_subsystems[8]->name, "200");

	_subsystems[8]->log_level = yall_inherited_level;
	_subsystems[8]->output_type = yall_inherited_output;
	_subsystems[8]->previous = NULL;
	_subsystems[8]->next = NULL;
	_subsystems[8]->parent = _subsystems[7];
	_subsystems[8]->childs = NULL;

	/* Subsystem 201 */
	_subsystems[9] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->childs->childs->next = _subsystems[9];

	_subsystems[9]->name = malloc(sizeof("201")+1);
	strcpy(_subsystems[9]->name, "201");

	_subsystems[9]->log_level = yall_debug;
	_subsystems[9]->output_type = yall_inherited_output;
	_subsystems[9]->previous = _subsystems[8];
	_subsystems[9]->next = NULL;
	_subsystems[9]->parent = _subsystems[7];
	_subsystems[9]->childs = NULL;

	_subsystems[8]->next = _subsystems[9];

	/* Subsystem 3 */
	_subsystems[3] = malloc(sizeof(struct yall_subsystem));
	subsystems->next->next->next = _subsystems[3];

	_subsystems[3]->name = malloc(sizeof("3")+1);
	strcpy(_subsystems[3]->name, "3");

	_subsystems[3]->log_level = yall_err;
	_subsystems[3]->output_type = yall_console_output;
	_subsystems[3]->previous = _subsystems[2];
	_subsystems[3]->next = NULL;
	_subsystems[3]->parent = NULL;
	_subsystems[3]->childs = NULL;

	_subsystems[2]->next = _subsystems[3];
}

void clean_subsystems(void)
{
	for (int i = 0; i < 10; ++i) {
		free(_subsystems[i]->name);
		free(_subsystems[i]);
	}
}
