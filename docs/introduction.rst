*******************
Introduction
*******************

`yall` is a lightweight multiplatform C / C++ subsystems based logging library.

Philosophy
*******************

`yall` aims to simplify logs management for C and C++ application by providing a semi-high-level API. Through subsystems creations it can allow different set a logging parameters in order to provide multiple ways to alert application's developers / users.

Features
*******************

* C / C++ compatible.
* Subsystems to handle different set of logging parameters.
* Write logs inside console or file.
* Call custom function to logs formatting.
* Use specific lockless thread to avoiding latency.
* Runs on Linux and Windows (build with GCC, MSVC 12 & MSVC 14).