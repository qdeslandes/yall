# Project yall

[![license](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](COPYING)
[![Version](https://img.shields.io/github/release/Naccyde/yall.svg?label=version&colorB=ff0000)](https://github.com/Naccyde/yall/releases/latest)

|master >|[![Travis branch](https://img.shields.io/travis/Naccyde/yall/master.svg?label=linux)]()|[![AppVeyor branch](https://img.shields.io/appveyor/ci/Naccyde/yall/master.svg?label=windows)]()|[![SonarQube Coverage](https://img.shields.io/sonar/http/sonarqube.com/yall/coverage.svg)]()|
|---|---|---|---|---|
|develop >|[![Travis branch](https://img.shields.io/travis/Naccyde/yall/develop.svg?label=linux)]()|[![AppVeyor branch](https://img.shields.io/appveyor/ci/Naccyde/yall/develop.svg?label=windows)]()|[![SonarQube Coverage](https://img.shields.io/sonar/http/sonarqube.com/yall:develop/coverage.svg)]()|

YALL is a subsystems based logging library. It allow to handle multiple ways to log message for differents parts of an application thanks to subsystems creation. Subsystems can inherit from one another, override parents parameters, ...

### Log levels

Log levels are based on BSD Syslog Protocol (`RFC 3164`), they are stored as a `yall_log_level` type in an enumeration. The higher the value, the higher the criticality :
* 0 : `yall_debug`
* 1 : `yall_info`
* 2 : `yall_notice`
* 3 : `yall_warning`
* 4 : `yall_err`
* 5 : `yall_crit`
* 6 : `yall_alert`
* 7 : `yall_emerg`

### Subsystem

Subsystems are a way to manage differents logging configurations at runtime. An application can use different subystems in the same time to handle in a different way 2 or more part of it.

A subsystem is composed of :
* A name, it will be used to retrieved the subsystem or log informations into it.
* A minimal log level. If the logging macro level is equal or superior to the subsystem log level, the message will be logged.
* An output type, too choose where to output the log messages : file, console or both.
* The name of the output file (full path). This value can be NULL if the choosen output type is `yall_console_output`.
* A list of subsystem's childs.
* The next subsystem in the subsystems list.

Log level, output type and output file can be inherited from a parent.

If a parameter of the subsystem is not correct, the default one will be used.

### Calls

There is differents ways to log a message :
* `YALL_<log_level>(<subsystem>, <format>, ...)` : log the message according to <subsystem>'s parameters and <format>. The format parameters is a printf() like format with unlimited number of arguments.
* `YALL_<log_level>(<subsystem>, <condition>, <format>, ...)` : same as the previous function, but log the message only if the <condition> evals to true.
* `YALL_CALL_<log_level>(<subsystem>, <function>, <args>)` : call <function> with a fixed length buffer and <args> as parameters. <function> must then fill the buffer which will be displayed with the given subsystem's parameters. Useful to display structure or classes content with in a readable way.
* `YALL_CALL_<log_level>_IF(<subsystem>, <expr>, <function>, <args>)` : same as the previous function, but the message is displayed only if the expression evaluates to true.

### Example

```
#include <yall/yall.h>

yall_init();
yall_set_subsystem(
    "example_subsystem", /* Subsystem's name */
		NULL, /* Parent's name */
		yall_notice, /* Minimal log level */
		yall_file_output, /* Output type */
		"/var/log/mylog.log" /* Output file */
)

YALL_DEBUG("example_subsystem", "My message : %s", "error");
```

### Misc

Feel free to contribute to the project and send a pull request. To get some personnal help or report a bug, you can contact `naccyde <at> naccyde <dot> eu` ;) .
