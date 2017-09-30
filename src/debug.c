#include "yall/debug.h"

#include "yall/yall.h"
#include "yall/subsystem.h"

static bool debug = false;

void yall_enable_debug(void)
{
#ifdef DEBUG
        if (! yall_is_init())
                return;

        /*
         * The order of the following instructions is critical : first we
         * define the subsystem, but the debug flag must be set to false.
         * Otherwise, it will search for the subsystem before creating it,
         * it will not find it and then try to log a debug message to
         * inform the user this subsystem is not found, which will lead
         * to a call to get_subsystem() which will search the subsystem,
         * but it will not find it, ...
         */

        yall_set_subsystem("yall", NULL, yall_debug, yall_console_output, NULL);
        
        debug = true;
        
        _YALL_DBG_DEBUG("Debug mode activated");
#endif
}

void yall_disable_debug(void)
{
#ifdef DEBUG
        if (! yall_is_init())
                return;

        _YALL_DBG_DEBUG("Debug mode disactivated");

        debug = false;
        _free_subsystems(remove_subsystem("yall"));
#endif
}

bool yall_is_debug(void)
{
        return debug;
}