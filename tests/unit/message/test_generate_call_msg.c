#include "test_message.h"

/*
 * Len equals 0
 */
Test(message, test_generate_call_message0)
{
	char buffer[64] = { 0 };
	struct yall_call_data d = { 3, NULL, NULL };
	d.header = strdup("");

	struct yall_call_data_line *l = malloc(sizeof(struct yall_call_data_line));
	l->content = strdup("2");
	l->next = NULL;

	struct yall_call_data_line *m = malloc(sizeof(struct yall_call_data_line));
	m->content = strdup("1");
	m->next = l;

	struct yall_call_data_line *n = malloc(sizeof(struct yall_call_data_line));
	n->content = strdup("0");
	n->next = m;

	d.lines = n;

	generate_call_msg(buffer, 0, &d);

	cr_assert_str_eq(buffer, "");
}

/*
 * Too long
 */
Test(message, test_generate_call_message1)
{
	char buffer[2] = { 0 };
	struct yall_call_data d = { 3, NULL, NULL };
	d.header = strdup("");

	struct yall_call_data_line *l = malloc(sizeof(struct yall_call_data_line));
	l->content = strdup("2");
	l->next = NULL;

	struct yall_call_data_line *m = malloc(sizeof(struct yall_call_data_line));
	m->content = strdup("1");
	m->next = l;

	struct yall_call_data_line *n = malloc(sizeof(struct yall_call_data_line));
	n->content = strdup("0");
	n->next = m;

	d.lines = n;

	generate_call_msg(buffer, 2, &d);

	cr_assert_str_eq(buffer, "0");
}

/*
 * Short lines
 */
Test(message, test_generate_call_message2)
{
	char buffer[64] = { 0 };
	struct yall_call_data d = { 3, NULL, NULL };
	d.header = strdup("");

	struct yall_call_data_line *l = malloc(sizeof(struct yall_call_data_line));
	l->content = strdup("2");
	l->next = NULL;

	struct yall_call_data_line *m = malloc(sizeof(struct yall_call_data_line));
	m->content = strdup("1");
	m->next = l;

	struct yall_call_data_line *n = malloc(sizeof(struct yall_call_data_line));
	n->content = strdup("0");
	n->next = m;

	d.lines = n;

	generate_call_msg(buffer, 32, &d);

	cr_assert_str_eq(buffer, "012");
}

/*
 * Longer lines
 */
Test(message, test_generate_call_message3)
{
	char buffer[64] = { 0 };
	struct yall_call_data d = { 3, NULL, NULL };
	d.header = strdup("foo");

	struct yall_call_data_line *l = malloc(sizeof(struct yall_call_data_line));
	l->content = strdup("bar");
	l->next = NULL;

	struct yall_call_data_line *m = malloc(sizeof(struct yall_call_data_line));
	m->content = strdup("foobar");
	m->next = l;

	struct yall_call_data_line *n = malloc(sizeof(struct yall_call_data_line));
	n->content = strdup("foofoo");
	n->next = m;

	d.lines = n;

	generate_call_msg(buffer, 32, &d);

	cr_assert_str_eq(buffer, "foofoofoofoobarbar");
}