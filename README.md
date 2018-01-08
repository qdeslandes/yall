# Project yall

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Naccyde/yall/develop/LICENSE)
[![Version](https://img.shields.io/github/release/Naccyde/yall.svg?label=version&colorB=ff0000)](https://github.com/Naccyde/yall/releases/latest)

[![!][1mb]][1ml] [![!][2mb]][2ml] [![!][3mb]][3ml] [![!][4mb]][4ml]

YALL is a subsystems based logging library. It allow to handle multiple ways to log message for differents parts of an application thanks to subsystems creation. Subsystems can inherit from one another, override parents parameters, ...

<!-- TOC depthFrom:2 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Log levels](#log-levels)
- [Subsystem](#subsystem)
	- [Change a subsystem status](#change-a-subsystem-status)
- [Calls](#calls)
	- [Call a custom function](#call-a-custom-function)
- [Close the library](#close-the-library)
- [Configuration](#configuration)
- [About multithreading](#about-multithreading)
- [C++](#c)
- [General informations](#general-informations)
- [Debugging](#debugging)
- [Example](#example)
- [Misc](#misc)
- [Contributing](#contributing)
	- [Contributing process](#contributing-process)

<!-- /TOC -->

## Requirements

To build yall properly you need :

* `criterion` : https://github.com/Snaipe/Criterion, used for unit testing. Set `criterion_HINTS` if the library is not installed in a system path on Linux.
* `pthread` : available by default on Linux, check https://sourceforge.net/projects/pthreads4w/ for windows version. Set `pthread_HINTS` if the library is not installed in a system path on Linux.
* To package :
  * `rpmbuild`

## Log levels

Log levels are based on BSD Syslog Protocol (`RFC 3164`), they are stored as a `yall_log_level` type in an enumeration. The higher the value, the higher the criticality :
* 0 : `yall_debug`
* 1 : `yall_info`
* 2 : `yall_notice`
* 3 : `yall_warning`
* 4 : `yall_err`
* 5 : `yall_crit`
* 6 : `yall_alert`
* 7 : `yall_emerg`

## Subsystem

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

### Change a subsystem status

Functions are available to enable / disable a given subsystem. By default, on creation, a subsystem is enabled. On subsystem update, the status is not changed. The status of a subsystem is inheritable.

```
yall_enable_subsystem(<name>);
yall_disable_subsystem(<name>);
```

On a subsystem is disabled, no log message will be displayed of wrote.

## Calls

There is differents ways to log a message :
* `YALL_<log_level>(<subsystem>, <format>, ...)` : log the message according to <subsystem>'s parameters and <format>. The format parameters is a printf() like format with unlimited number of arguments.
* `YALL_<log_level>(<subsystem>, <condition>, <format>, ...)` : same as the previous function, but log the message only if the <condition> evals to true.
* `YALL_CALL_<log_level>(<subsystem>, <function>, <args>)` : call <function> with a fixed length buffer and <args> as parameters. <function> must then fill the buffer which will be displayed with the given subsystem's parameters. Useful to display structure or classes content with in a readable way.
* `YALL_CALL_<log_level>_IF(<subsystem>, <expr>, <function>, <args>)` : same as the previous function, but the message is displayed only if the expression evaluates to true.

### Call a custom function

The function call mechanism has been improved to allow more flexibility and custom function call. To call the said custom function you must :
* Create the proper function with the following prototype : `void function(yall_call_data *, void *args)`. This function makes calls to :
  * `yall_call_set_header(yall_call_data *d, const char *header)` : the header used on the log message, the header can be unset.
  * `yall_call_add_line(yall_call_data *d, int indent, const char *content)` : a new line to the log message.
* Call to the proper macro : `YALL_CALL_<log_level>(<subsystem>, function, <args>)`.

## Close the library

The yall library contain a flag which store the number of times it has been initialized. Each library initializing the library with `yall_init()` will increment this counter. This allow us to keep track of the number of library using the library at runtime. This way, if a library close yall through `yall_close()`, the other parts of the application can still use it. Once the counter fall to 0, the library is freed. The endpoint of the application can call `yall_close_all()` which will close the library regardless of the number of instances.

## Configuration

Some configuration functions are available, they can be called before the initialization :
* `yall_config_set_std_header_template` : define the header placed in front of the log messages
* `yall_config_set_call_header_template` : define the header placed in front of the call log messages
* `yall_config_set_tab_width` : define the width (in characters) of the indentation of the call log messages

All these functions allow for `reset` and `get` instead of `set`, to reset their value or get it.

## About multithreading

Only the log writing functions are thread safe : `YALL_xxx` macros can be called from any thread. The formatter function can also be called from any thread (the library does not handle their atomicity).

On Linux, changing a subsystem status is atomic, it can be done from concurrent threads.

## C++

The `include` folder of the library contains `Yall.hpp` which defines a class to handle Yall in a C++ way. It can be used the same way as the library, except it handle some features through C++ facilities with static method only.

This class isn't a singleton, so `Yall::init()` must be called prior to anything else. Then, all the function of the library can be called normally through their static method. To change configuration, `Yall::config()` returns a `YallConfig` object.

The major difference between C function and C++ class is the custom formatters parameters :

```
void my_cpp_formatter(YallData &d, void *args)
{
	d.newLine(1) << "My string";
	d.newLine(2) << "My string and << myVar;
}
```

The custom C++ formatters use a `YallData` reference and `YallData::newLine()` to get a reference to a new line, the width of the line indent can be passed as a parameter.

See `tests/cpp/main.cpp` for more informations.

## General informations

Header format is customizable, its length is hardcoded to 64 bytes, this means the format itself can't be longer than 63 characters. The resulting generated format placed in front of the log message can be longer.

## Debugging

If yall produce a strange behaviour, it is possible to get debug informations in runtime. To do this, you must run the debug version of the library (`yalld`), and enable debug mode through `yall_enable_debug()`. The library will automatically create a `yall` subsystem and print the log messages. This subsystem write logs in console with a minimal log level of `yall_debug`.

This subsystem parameters can be changed outside the library with `yall_set_subsystem()`.

Obviously, this means the `yall` subsystem is reserved for the library use, otherwise the debug mode will use a user defined subsystem.

Some of the library functions returns a `yall_error` type, which is an error code for the library. A nul terminated string corresponding to this code can be retrieved through `yall_strerror(code)`.

## Example

Some real life examples are available inside C and C++ test projects : `tests/c/main.c` and `test/cpp/main.cpp`.

## Misc

A log coloration scheme for NotePad++ is available in the resources folder.

## Contributing

yall is an open-source project, feel free to contribute to the project and send a pull request. To get some personnal help or report a bug, you can contact `naccyde <at> naccyde <dot> eu` ;) .

All contributions must fork `master` to create a `feature/<myfeature>` branch, then do a PR on `master`. All work should follow the [Linux kernel coding rules](https://www.kernel.org/doc/html/v4.10/process/coding-style.html), `checkstyle` script is available to enforce these guidelines.

The CMake system used define several targets :

* `yall` : generate yall library objects.
* `yall_static` : link yall library objects as a static library.
* `yall_shared` : link yall library objects as a shared library.
* `yall_c` : generate C test project.
* `yall_cpp` : generate CPP test project.
* `yall_unit` : generate unit tests.
* `checkstyle` : run `resources/checkstyle.sh` script, from the Linux kernel sources, it parses sources to check coding guidelines.
* `resume_coverage` : works with Firefox on Fedora and Debian (not tested elsewhere). It opens an HTML report about tests coverage.
* `validate` : run a Python script which check binaries with Valgrind, tests, coverage, coding style...
* `validate_full` : same as `validate` but perform a CMake generation and compilation.
* `test` : CMake target, run tests : unit tests, checkstyle, tests coverage and `yall_c` and `yall_cpp` through Valgrind.
* `install` : CMake target, install the project to `${CMAKE_INSTALL_PREFIX}`.
* `package` : CMake target, create zip archive from the installed binaries.

Some other target are available, their names start with `__`, which means there is no reason to start them manually.

### Contributing process

The process to contribute to yall is the following :

* Create a branch from `master` named `feature/<my_feature>`.
* *Coding time*
* Ensure the sources builds
* Ensure tests (`make test`) succeed.
* Create a pull request on GitHub.
* Wait for some review and for CI to build.


[1mb]: https://img.shields.io/travis/Naccyde/yall/master.svg?label=linux
[1ml]: https://travis-ci.org/Naccyde/yall/branches
[2mb]: https://img.shields.io/appveyor/ci/Naccyde/yall/master.svg?label=windows
[2ml]: https://ci.appveyor.com/project/Naccyde/yall
[3mb]: https://sonarcloud.io/api/badges/gate?key=yall
[3ml]: https://sonarcloud.io/dashboard?id=yall
[4mb]: https://sonarcloud.io/api/badges/measure?key=yall&metric=coverage
[4ml]: https://sonarcloud.io/dashboard?id=yall