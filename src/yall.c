/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/yall.h"

#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "yall/utils.h"
#include "yall/errors.h"
#include "yall/writer.h"
#include "yall/message.h"
#include "yall/subsystem.h"
#include "yall/debug.h"

#include "version.h"
#define YALL_VERSION_STR STRINGIFY(YALL_MAJOR) "." STRINGIFY(YALL_MINOR) "." STRINGIFY(YALL_PATCH)

static uint32_t version = (YALL_MAJOR << 16) | (YALL_MINOR << 8) | YALL_PATCH;
static const char *version_string = "yall, Quentin <Naccyde> Deslandes, version " YALL_VERSION_STR;

uint32_t yall_get_version(void)
{
        return version;
}

const char *yall_get_version_string(void)
{
        return version_string;
}

static uint16_t initialized = 0;

uint8_t yall_init(void)
{
        uint8_t ret = YALL_OK;

        if (initialized) {
                ++initialized;
                ret = YALL_ALREADY_INIT;
                goto end;
        }

        ++initialized;

        if ((ret = writer_init()))
                goto err;

end:
        return ret;
err:
        --initialized;
        return ret;
}

uint8_t yall_is_init(void)
{
        return initialized;
}

uint8_t yall_log(const char *subsystem,
        enum yall_log_level log_level,
        const char *function,
        const char *format,
        ...)
{
        uint8_t ret = YALL_OK;

        char *msg = NULL;
        struct yall_subsystem_params p = { 0 };

        if (! initialized) {
                ret = YALL_NOT_INIT;
                goto end;
        }

        /*
         * Find the subsystem's parameters. Useless to get the subsystem, or
         * to know if it is found. If the subsystem is not found, we use the
         * default parameters.
         */
        get_subsystem(subsystem, &p);

        if (p.status == yall_subsys_disable) {
                ret = YALL_SUBSYS_DISABLED;
                goto end;
        }

        if (log_level < p.log_level) {
                ret = YALL_LOG_LEVEL_TOO_LOW;
                goto end;
        }

        // Create message
        if (! (msg = malloc(YALL_MSG_LEN))) {
                ret = YALL_NO_MEM;
                goto end;
        }

        va_list args;
        va_start(args, format);
        generate_message(msg,
                format,
                subsystem,
                log_level,
                function,
                args);
        va_end(args);

        // Write message
        ret = write_msg(p.output_type, log_level, p.output_file, msg);

end:
        free(msg);
        return ret;
}

uint8_t yall_call_log(const char *subsystem,
        enum yall_log_level log_level,
        const char *function_name,
        void (*formatter)(yall_call_data *d, void *args),
        void *args)
{
        uint8_t ret = YALL_OK;
        char *message = NULL;
        struct yall_subsystem_params p = { 0 };

        if (! initialized) {
                ret = YALL_NOT_INIT;
                goto end;
        }

        get_subsystem(subsystem, &p);

        if (p.status == yall_subsys_disable) {
                ret = YALL_SUBSYS_DISABLED;
                goto end;
        }

        if (log_level < p.log_level) {
                ret = YALL_LOG_LEVEL_TOO_LOW;
                goto end;
        }

        struct yall_call_data d = { 0 };
        init_call_data(&d);

        formatter(&d, args);

        // All '+ 1' here are the \0 terminating character
        message = malloc(MSG_HEADER_LEN + d.message_size + 1);
        generate_header(message, subsystem, log_level, function_name);

        convert_data_to_message(&message[strlen(message)], d.message_size + 1, &d);

        ret = write_msg(p.output_type, log_level, p.output_file, message);

end:
        free(message);
        return ret;
}

uint8_t yall_set_subsystem(const char *name,
        const char *parent,
        enum yall_log_level log_level,
        enum yall_output_type output_type,
        const char *output_file)
{
        uint8_t ret = YALL_OK;

        if (! initialized) {
                ret = YALL_NOT_INIT;
                goto end;
        }

        if (! name) {
                ret = YALL_NO_NAME;
                goto end;
        }

        struct yall_subsystem *s = remove_subsystem(name);

        if (! s) {
                s = create_subsystem(name, log_level, output_type, output_file);

                if (! s) {
                        ret = YALL_CANT_CREATE_SUBSYS;
                        goto end;
                }
        } else {
                update_subsystem(s, log_level, output_type, output_file);
        }

        add_subsystem(parent, s);

end:
        return ret;
}

uint8_t yall_close(void)
{
        uint8_t ret = YALL_OK;

        if (! initialized) {
                ret = YALL_NOT_INIT;
                goto end;
        }

        if (1 == initialized) {
                _YALL_DBG_INFO("Close library");
                yall_disable_debug();
                writer_close();
                free_subsystems();
                initialized = 0;
        } else {
                --initialized;
        }

end:
        return ret;
}

void yall_close_all(void)
{
        for ( ; yall_close() != YALL_NOT_INIT ; ) ;
}
