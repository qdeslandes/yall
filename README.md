# Project yall

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Naccyde/yall/develop/LICENSE)
[![Version](https://img.shields.io/github/release/Naccyde/yall.svg?label=version&colorB=ff0000)](https://github.com/Naccyde/yall/releases/latest)

https://sonarcloud.io/api/badges/gate?key=yall
https://sonarcloud.io/api/badges/measure?key=yall&metric=coverage

[Travis branch](https://img.shields.io/travis/Naccyde/yall/master.svg?label=linux)

|master > | [![!][1mb]][1ml] | [![!][2mb]][2ml] | [![!][3mb]][3ml] | [![!][4mb]][4ml] |
|---|---|---|---|---|
|develop >| [![!][1db]][1dl] | [![!][2db]][2dl] | [![!][3db]][3dl] | [![!][4db]][4dl] |

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

#### Change a subsystem status

Functions are available to enable / disable a given subsystem. By default, on creation, a subsystem is enabled. On subsystem update, the status is not changed. The status of a subsystem is inheritable.

```
yall_enable_subsystem(<name>);
yall_disable_subsystem(<name>);
```

On a subsystem is disabled, no log message will be displayed of wrote.

### Calls

There is differents ways to log a message :
* `YALL_<log_level>(<subsystem>, <format>, ...)` : log the message according to <subsystem>'s parameters and <format>. The format parameters is a printf() like format with unlimited number of arguments.
* `YALL_<log_level>(<subsystem>, <condition>, <format>, ...)` : same as the previous function, but log the message only if the <condition> evals to true.
* `YALL_CALL_<log_level>(<subsystem>, <function>, <args>)` : call <function> with a fixed length buffer and <args> as parameters. <function> must then fill the buffer which will be displayed with the given subsystem's parameters. Useful to display structure or classes content with in a readable way.
* `YALL_CALL_<log_level>_IF(<subsystem>, <expr>, <function>, <args>)` : same as the previous function, but the message is displayed only if the expression evaluates to true.

#### Call a custom function

The function call mechanism has been improved to allow more flexibility and custom function call. To call the said custom function you must :
* Create the proper function with the following prototype : `void function(yall_call_data *, void *args)`. This function makes calls to :
  * `yall_call_set_header(yall_call_data *d, const char *header)` : the header used on the log message, the header can be unset.
  * `yall_call_add_line(yall_call_data *d, int indent, const char *content)` : a new line to the log message.
* Call to the proper macro : `YALL_CALL_<log_level>(<subsystem>, function, <args>)`.

### Close the library

The yall library contain a flag which store the number of times it has been initialized. Each library initializing the library with `yall_init()` will increment this counter. This allow us to keep track of the number of library using the library at runtime. This way, if a library close yall through `yall_close()`, the other parts of the application can still use it. Once the counter fall to 0, the library is freed. The endpoint of the application can call `yall_close_all()` which will close the library regardless of the number of instances.

### About multithreading

Subsystems creation and manipulation is not thread safe. Subsystems should not be manipulated in different thread, but calling for log writing can be done from anywhere. Support for multithread subsystems creation will be done in a not so long future.

On Linux, changing a subsystem status is atomic, it can be done from concurrent threads.

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

yall is an open-source project, feel free to contribute to the project and send a pull request. To get some personnal help or report a bug, you can contact `naccyde <at> naccyde <dot> eu` ;) .


[1mb]: https://img.shields.io/travis/Naccyde/yall/master.svg?label=linux
[1ml]: https://travis-ci.org/Naccyde/yall/branches
[2mb]: https://img.shields.io/appveyor/ci/Naccyde/yall/master.svg?label=windows
[2ml]: https://ci.appveyor.com/project/Naccyde/yall
[3mb]: https://sonarcloud.io/api/badges/gate?key=yall
[3ml]: https://sonarcloud.io/dashboard?id=yall
[4mb]: https://sonarcloud.io/api/badges/measure?key=yall&metric=coverage
[4ml]: https://sonarcloud.io/dashboard?id=yall

[1db]: https://img.shields.io/travis/Naccyde/yall/develop.svg?label=linux
[1dl]: https://travis-ci.org/Naccyde/yall/branches
[2db]: https://img.shields.io/appveyor/ci/Naccyde/yall/develop.svg?label=windows
[2dl]: https://ci.appveyor.com/project/Naccyde/yall
[3db]: https://sonarcloud.io/api/badges/gate?key=yall:develop
[3dl]: https://sonarcloud.io/dashboard?id=yall:develop
[4db]: https://sonarcloud.io/api/badges/measure?key=yall:develop&metric=coverage
[4dl]: https://sonarcloud.io/dashboard?id=yall:develop
