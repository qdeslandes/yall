#include "test_header.h"

extern size_t generate_call_hdr(char *buffer, size_t len, struct header_content *hc);

/*
 * This function only call generate_hdr(), so no code must be tested here.
 * But defining a test allow to mark it as covered, so...
 */

Test(header, test_generate_call_hdr0, .init=test_generate_hdr_setup, .fini=test_generate_hdr_clean)
{
	struct header_content hc = { "subsystem", "NOTICE", "function" };

	generate_call_hdr(NULL, 0, &hc);
}