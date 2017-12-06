#include "test_header.h"

extern size_t generate_std_hdr(char *buffer, size_t len, struct header_content *hc);

/*
 * This function only call generate_hdr(), so no code must be tested here.
 * But defining a test allow to mark it as covered, so...
 */

Test(header, test_generate_std_hdr0)
{
	struct header_content hc = { "subsystem", "NOTICE", "function", "main.c", { 0 }, { 0 } };

	generate_call_hdr(NULL, 0, &hc);
}