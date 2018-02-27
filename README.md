# yall

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Naccyde/yall/develop/LICENSE)

[![!][1b]][1l] [![!][2b]][2l] [![!][3b]][3l] [![!][4b]][4l]

`yall` is a subsystems based logging library. It allow to handle multiple ways to log message for differents parts of an application thanks to subsystems creation. Subsystems can inherit from one another, override parents parameters, ...

`yall` is available on Linux and Windows (MSVC12 and MSVC14).


## How to use

Informations about how to use `yall` can be found on the [project wiki](https://naccyde.gitlab.io/yall/). As the documentation is under redaction, the old one can be found in [Git history](https://gitlab.com/naccyde/yall/blob/755569d405948297665aeaad41d4bb9f7856ad35/README.md).

The major steps are :
  * Initialize the library
  * Create subsystems
  * Log messages


## Build

Git LFS is required to clone the repository. yall use CMake as build system generator, so, ensure CMake is installed on your system (version `3.6` minimum). The following dependencies are also required :

* `gcc` and `g++`.
* `pthread` : a [Windows version](https://sourceforge.net/projects/pthreads4w/) is available. Installed by default on Linux.
* `jansson` : JSON parsing library.
* `doxygen` : used to generate documentation.
* `criterion` : available on [Github](https://github.com/Snaipe/Criterion). Used for unit testing. On Windows, it is available inside `external` folder.
* `valgrind` (optional, Linux only) : some tests scripts use it to test the library.
* `rpmbuild` and `debbuild` (optional, Linux only) : to generate Linux packages.
* `python-sphinx`, `python-sphinx-rtd-theme` and `breathe` (optional, Linux) : to build the user documentation.

Then :

    cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=<Release|Debug>
    make -C build

Launched inside the sources directory, these commands will create a `build` directory to run CMake inside, and build the library. The `CMAKE_BUILD_TYPE` variable will define what will be installed. On `Release` build, only required parts to use the library will be build and installed. On `Debug` build, all the required file to build with the library will be build and installed.

On Windows, the process is straightforward using CMake GUI and Visual Studio.


## Installation

Once library is build, install it with :

    sudo make -C build install

It requires `sudo` as the file are installed on the system in `/usr/local`.


## Contribute

The way to contribute to the project is define is `CONTRIBUTING.md` (currently under development).


## Troubleshooting

For any problem that can't be solved using `Debugging` section of the documentation, there is multiple solutions :

* Create an [issue](https://gitlab.com/naccyde/yall/issues) on the project, following the template.
* Send a mail to the project's service desk : `incoming+naccyde/yall <at> gitlab <dot> com`.
* Send a mail to the maintainer : `naccyde <at> naccyde <dot> eu`.


[1b]: https://gitlab.com/naccyde/yall/badges/master/pipeline.svg
[1l]: https://gitlab.com/naccyde/yall/commits/master
[2b]: https://sonarcloud.io/api/badges/gate?key=yall
[2l]: https://sonarcloud.io/dashboard?id=yall
[3b]: https://sonarcloud.io/api/badges/measure?key=yall&metric=coverage
[3l]: https://sonarcloud.io/dashboard?id=yall
[4b]: https://sonarcloud.io/api/badges/measure?key=yall&metric=sqale_debt_ratio
[4l]: https://sonarcloud.io/dashboard?id=yall

