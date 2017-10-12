#include <stdio.h>

#include <yall/yall.h>

void memoryInfos(struct yall_call_data *d, const void *args)
{
        (void)(args);

        yall_call_add_line(d, 0, "======= Backtrace: =========");
        yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x70bfb)[0x7ff9cd0bfbfb]");
        yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x76fc6)[0x7ff9cd0c5fc6]");
        yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x7780e)[0x7ff9cd0c680e]");
        yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x35940)[0x7ff9cd084940]");
        yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(+0x3599a)[0x7ff9cd08499a]");
        yall_call_add_line(d, 1, "/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf8)[0x7ff9cd06f2e8]");

        yall_call_add_line(d, 0, "======== Memory map: ========");
        yall_call_add_line(d, 1, "55d5e5d8c000-55d5e5dbe000 rw-p 00000000 00:00 0                          [heap]");
        yall_call_add_line(d, 1, "7ff9c8000000-7ff9c8021000 rw-p 00000000 00:00 0 ");
        yall_call_add_line(d, 1, "7ff9c8021000-7ff9cc000000 ---p 00000000 00:00 0 ");
        yall_call_add_line(d, 1, "7ff9cd04f000-7ff9cd1e2000 r-xp 00000000 08:06 4195034                    /lib/x86_64-linux-gnu/libc-2.24.so");
        yall_call_add_line(d, 1, "7ff9cd1e2000-7ff9cd3e2000 ---p 00193000 08:06 4195034                    /lib/x86_64-linux-gnu/libc-2.24.so");
}

int main(void)
{
        yall_init();

        #ifdef DEBUG
        yall_enable_debug();
        #endif
        
        yall_config_set_tab_width(4);
        yall_config_set_std_header_template("[%d] :: %-9l : %s : \n\t");
        yall_config_set_call_header_template("[%d] :: %-9l : %s : ");
        
        yall_set_subsystem("yall_cpp_test", NULL, yall_debug, yall_console_output, NULL);
        yall_set_subsystem("io", "yall_cpp_test", yall_debug, yall_console_output, NULL);
        yall_set_subsystem("memory", "yall_cpp_test", yall_debug, yall_console_output, NULL);

        YALL_DEBUG("yall_cpp_test", "%s, %d", yall_get_version_string(), yall_get_version());
        YALL_DEBUG("io", "IO subsystem ready.");
        YALL_CALL_ERR("memory", memoryInfos, NULL);

        yall_set_subsystem("scheduler", "yall_test_cpp", yall_debug, yall_console_output, NULL);

        YALL_ALERT("scheduler" , "Using process 7034.");

        yall_disable_subsystem("scheduler");
        YALL_DEBUG("scheduler", "Starting process 52233.");
        yall_enable_subsystem("scheduler");

#ifdef _WIN32
        getchar();
#endif

        yall_close_all();

        return 0;
}
