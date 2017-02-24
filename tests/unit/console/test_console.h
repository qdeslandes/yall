#ifndef _H_TESTS_CONSOLE
#define _H_TESTS_CONSOLE

#include "yall/yall.h"

struct param_set_color {
    enum yall_log_level ll;
    uint8_t code;
};

extern struct param_set_color ll_and_colors[8];

#endif
