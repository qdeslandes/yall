#include "test_yall.h"

static void tests_yall_setup(void)
{
        _tests_hide_stderr();
}

static void tests_yall_clean(void)
{
        _tests_restore_stderr();
        remove(default_params.output_file);
}

TestSuite(yall, .init=tests_yall_setup, .fini=tests_yall_clean);

void tests_yall_init_lib(void)
{
        yall_init();
}

void tests_yall_close_lib(void)
{
        while (yall_close() != YALL_NOT_INIT) ;
}

void tests_yall_log_setup(void)
{
        yall_init();
        create_subsystems();
}

void tests_yall_log_clean()
{
        clean_subsystems();

        while (yall_close() != YALL_NOT_INIT);
}

void tests_call_log_function(struct yall_call_data *d, const void *args)
{
        /*
         * Writing function used in yall_call_log.
         */
}
