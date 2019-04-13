# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
### Changed
### Deprecated
### Removed
* Windows support. `legacy` branch remains compatible.
### Fixed
### Security

## [1.8.1]
### Added
* `CONTRIBUTING.md`
* Check parameter's output file when calling `_get_subsystem()`
### Changed
* Enforce use of explicit data types (e.g. `int32_t` instead of `int`)
* Remove call data limited line length
* Change `init_call_data()` to `call_new()` and `call_delete()`
* Use `llist` instead of a custom linked-list for call data
### Deprecated
### Removed
* `coverage.py` for Codacy coverage
* `message_delete_wrapper()` function
* `convert_data_to_message()` function
### Fixed
* Show subsystems names inside tree ([#146](https://github.com/naccyde/yall/issues/176))
* Update subsystem name correctly when using an existing subsystem name
* Removing a subsystem now display the proper log message
### Security

## [1.8.0]
### Added
* Queue (non concurrent) mechanism
* List mechanism
### Changed
* Set queue as cqueue (concurrent queue)
* Temporary disable unstable unit tests  (start_thread() on Windows)
### Deprecated
### Removed
### Fixed
* Add `-g` flag to unit test debug build
* Thread loop timer (integer overflow)
* Stack overflow when too many messages are printed
* Artifacts deployment script
* Release script (reduce number of commits on develop)
* Sonar analysis
### Security

## [1.7.7]
### Added
### Changed
### Deprecated
### Removed
### Fixed
### Security

## [1.7.6]
### Added
### Changed
### Deprecated
### Removed
### Fixed
### Security
