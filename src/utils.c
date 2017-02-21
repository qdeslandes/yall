#include "yall/utils.h"

#include <string.h>

const char *_yall_funcname(const char *f)
{
	int dots = 0;
	int len = strlen(f);

	for (; len >= 0; --len) {
		if (f[len] == ':')
			++dots;

		if (dots == 3 || f[len] == ' ')
			return &f[len+1];
	}

	return f;
}
