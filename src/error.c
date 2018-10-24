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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/error.h"

#define YALL_ERROR(code, msg) { code, msg }

static struct {
	yall_error code;
	const char *message;
} errordesc[] = {
	/* Generic messages */
	YALL_ERROR(YALL_SUCCESS, "Success."),
	YALL_ERROR(YALL_UNKNOW_ERROR,
		"Unknow error happened. Please contact the developpers."),

	/* Library setup */
	YALL_ERROR(YALL_ALREADY_INIT, "Library already initialized."),
	YALL_ERROR(YALL_NOT_INIT, "Library not initialized."),
	YALL_ERROR(YALL_SEM_INIT_ERR, "Error during semaphore initialization."),
	YALL_ERROR(YALL_NO_MEM, "No memory available."),
	YALL_ERROR(YALL_LOG_LEVEL_TOO_LOW,
		"Message not processed, log level set too low."),

	/* Subsystem errors */
	YALL_ERROR(YALL_SUBSYS_NO_NAME, "No subsystem name."),
	YALL_ERROR(YALL_SUBSYS_NOT_EXISTS, "Given subsystem does not exists."),
	YALL_ERROR(YALL_SUBSYS_DISABLED, "Subsystem disabled."),
	YALL_ERROR(YALL_CANT_CREATE_SUBSYS, "Could not create subsystem."),

	/* File output errors */
	YALL_ERROR(YALL_FILE_LOCK_ERR, "Could not lock log file."),
	YALL_ERROR(YALL_FILE_OPEN_ERR, "Could not open log file."),

	/* Console output errors */
	YALL_ERROR(YALL_CONSOLE_LOCK_ERR, "Could not lock console."),
	YALL_ERROR(YALL_CONSOLE_WRITE_ERR, "Could not write on console."),

	/* Threading system */
	YALL_ERROR(YALL_CANT_CREATE_THREAD, "Writing thread can't be created."),

	/* JSON configuration */
	YALL_ERROR(YALL_JSON_CANT_READ_CONFIG,
		"Could not read JSON configuration."),
	YALL_ERROR(YALL_JSON_UNDECLARED_SUBSYS,
		"Undefined subsystem in JSON configuration."),
	YALL_ERROR(YALL_JSON_CIRCLE_DEPENDENCY,
		"Circle dependency detected in JSON subsystems.")
};

const char *yall_strerror(yall_error err)
{
	if (err < 0 || err >= yall_err_end)
		return errordesc[YALL_UNKNOW_ERROR].message;

	return errordesc[err].message;
}
