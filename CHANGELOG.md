# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
* Ensure `test_show_subsystems_tree` has output on stderr
* Check parameter's output file when calling `_get_subsystem()`
* Add `benchmark` sources subset to track performances evolution overtime
### Changed
* Use `int32_t` or `uint32_t` instead of `int` when possible
* Update `README.md`
* Add `CONTRIBUTING.md`
* Use `llist` instead of a standard linked-list for call data (improve speed)
### Deprecated
### Removed
* `message_delete_wrapper()` function
* `coverage.py` for Codacy coverage
### Fixed
* Show subsystems names inside tree ([#146](https://github.com/naccyde/yall/issues/176))
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