# yall contributing guide

## Unit tests

Unit tests have to be organized the following way:

```
tests
   ├─ <source_file>
   │  ├─ test_<function>.c
   │  ├─ test_<function>.c
   │  ├─ test.c
   │  └─ test.h
   ├─ <source_file>
   │  ├─ test_<function>.c
   │  ├─ test_<function>.c
   │  ├─ test.c
   │  └─ test.h
   ...
   ├─ test.c
   └─ yall_test.h
```

This way, `test.h` and `test.c` files in each folder will store fixtures for the given source file.

Then, each test case should describe a specific way of using the function, or should aim to trigger a particular error returned by the function.

Global coverage percentage should be at least 95%, otherwise continuous integration will fail. This is required in order to ensure most part of the library is covered by unit test and reduce potential errors. Following this logic, once a bug is found in the library, a test case reproducing it should first be wrote, this allow to check its resolution and avoid regressions.
