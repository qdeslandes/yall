#include "test_header.h"

extern bool is_modifier(char c, enum yall_matches *match);

/*
 * IS a modifier.
 */
Test(header, test_is_modifier0)
{
	enum yall_matches match = match_empty;

	cr_assert_eq(is_modifier('s', &match), true);
	cr_assert_eq(match, match_subsystem);

	cr_assert_eq(is_modifier('l', &match), true);
	cr_assert_eq(match, match_log_level);

	cr_assert_eq(is_modifier('f', &match), true);
	cr_assert_eq(match, match_function);

	cr_assert_eq(is_modifier('F', &match), true);
	cr_assert_eq(match, match_filename);

	cr_assert_eq(is_modifier('L', &match), true);
	cr_assert_eq(match, match_line);

	cr_assert_eq(is_modifier('d', &match), true);
	cr_assert_eq(match, match_date);
}

/*
 * Is NOT a modifier.
 */
Test(header, test_is_modifier1)
{
	enum yall_matches match = match_empty;

	cr_assert_eq(is_modifier('c', &match), false);
	cr_assert_eq(match, match_empty);

	cr_assert_eq(is_modifier('a', &match), false);
	cr_assert_eq(match, match_empty);
}
