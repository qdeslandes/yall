# yall

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/naccyde/yall/master/LICENSE)
[![Travis (.org) branch](https://img.shields.io/travis/naccyde/yall/master.svg?label=Linux)](https://travis-ci.com/naccyde/yall)
[![AppVeyor branch](https://img.shields.io/appveyor/ci/naccyde/yall/master.svg?label=Windows)](https://ci.appveyor.com/project/Naccyde/yall)
[![SonarQube Coverage](https://img.shields.io/sonar/http/sonarcloud.io/yall/coverage.svg)](https://sonarcloud.io/dashboard?id=yall)
[![SonarQube Tech Debt](https://img.shields.io/sonar/http/sonarcloud.io/yall/tech_debt.svg)](https://sonarcloud.io/dashboard?id=yall)

`yall` is a subsystems based logging library. It allows to create subsystems which will manage all the logging parameters for an area of the application. Subsystems can inherit from one another, override parents parameters...

`yall` is available on Linux and Windows (MSVC12 and MSVC14).


## How to use

Informations about how to use `yall` can be found on the [project wiki](https://naccyde.github.io/yall/).

The main workflow to use yall is the following:
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

    cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=Release
    make -C build

Launched inside the sources directory, these commands will create a `build` directory to run CMake inside, and build the library. The `CMAKE_BUILD_TYPE` variable will define what will be installed. `Release` here can be changed to `Debug`, to build the library with the debug symbols.

On Windows, the process is straightforward using CMake GUI and Visual Studio.


## Installation

Once library is build, install it with :

    sudo make -C build install

It requires `sudo` as the file are installed on the system in `/usr/local`.


## Contribute

The way to contribute to the project is define is `CONTRIBUTING.md` (currently under development).


## Troubleshooting

For any problem that can't be solved using `Debugging` section of the documentation, there is multiple solutions :

* Send a mail to the maintainer : `naccyde <at> naccyde <dot> eu`.
* Fork the repository and create a pull-request.
