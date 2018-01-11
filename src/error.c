#include "yall/error.h"

#define YALL_ERROR(code, msg) { code, msg }

struct yall_errordesc {
	yall_error code;
	const char *message;
};

static struct yall_errordesc errordesc[] = {
	YALL_ERROR(YALL_SUCCESS, "Success."),
	YALL_ERROR(YALL_UNKNOW_ERROR,
		"Unknow error happened. Please contact the developpers."),

	YALL_ERROR(YALL_ALREADY_INIT, "Library already initialized."),
	YALL_ERROR(YALL_NOT_INIT, "Library not initialized."),
	YALL_ERROR(YALL_SEM_INIT_ERR, "Error during semaphore initialization."),
	YALL_ERROR(YALL_NO_MEM, "No memory available."),
	YALL_ERROR(YALL_LOG_LEVEL_TOO_LOW,
		"Message not processed, log level set too low."),

	YALL_ERROR(YALL_NO_NAME, "No subsystem name."),

	YALL_ERROR(YALL_FILE_LOCK_ERR, "Could not lock log file."),
	YALL_ERROR(YALL_FILE_OPEN_ERR, "Could not open log file."),

	YALL_ERROR(YALL_CONSOLE_LOCK_ERR, "Could not lock console."),
	YALL_ERROR(YALL_CONSOLE_WRITE_ERR, "Could not write on console."),

	YALL_ERROR(YALL_STRING_WRITE_ERR, "Could not write in string."),

	YALL_ERROR(YALL_SUBSYS_NOT_EXISTS, "Given subsystem does not exists."),
	YALL_ERROR(YALL_SUBSYS_DISABLED, "Subsystem disabled."),

	YALL_ERROR(YALL_CANT_CREATE_SUBSYS, "Could not create subsystem."),

	YALL_ERROR(YALL_CANT_CREATE_THREAD, "Writing thread can't be created.")
};

const char *yall_strerror(yall_error err)
{
	if (err < 0 || err >= yall_err_end)
		return errordesc[YALL_UNKNOW_ERROR].message;

	return errordesc[err].message;
}
