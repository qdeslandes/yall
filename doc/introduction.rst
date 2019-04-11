*******************
Introduction
*******************

`yall` is a lightweight multiplatform C / C++ subsystem-based logging library.

Philosophy
*******************

`yall` aims to simplify logs management for C and C++ application by providing a semi-high-level API. Through subsystems creations it can allow different set a logging parameters in order to provide multiple ways to alert application's developers / users.

Features
*******************

* C / C++ compatible.
* Subsystems to handle differents sets of logging parameters.
* Write logs inside console or file.
* Call custom function to format logs output.
* Use specific lockless thread to avoiding latency.
* Runs on Linux (see `legacy` branch on GitHub for Windows support).
