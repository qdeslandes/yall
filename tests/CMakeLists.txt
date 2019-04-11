# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(benchmark)

add_subdirectory(unit)

configure_file(validation/yall.config ${CMAKE_BINARY_DIR}/binaries COPYONLY)

add_custom_target(unit_test
    COMMAND python3 ${CMAKE_SOURCE_DIR}/tests/validation/unit.py --binary ${CMAKE_BINARY_DIR}/binaries/yall_unit)

add_custom_target(c_test
    COMMAND python3 ${CMAKE_SOURCE_DIR}/tests/validation/valgrind.py --binary ${CMAKE_BINARY_DIR}/binaries/yall_c --config ${CMAKE_BINARY_DIR}/binaries/yall.config)

add_custom_target(cpp_test
    COMMAND python3 ${CMAKE_SOURCE_DIR}/tests/validation/valgrind.py --binary ${CMAKE_BINARY_DIR}/binaries/yall_cpp)

add_custom_target(style_test
    COMMAND python3 ${CMAKE_SOURCE_DIR}/tests/validation/checkstyle.py --sourcesDir ${CMAKE_SOURCE_DIR})

add_custom_target(coverage_test
    DEPENDS unit_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND python3 ${CMAKE_SOURCE_DIR}/tests/validation/coverage.py --sourcesDir ${CMAKE_SOURCE_DIR} --outDir ${CMAKE_BINARY_DIR}/out/coverage --gcnoDir ${CMAKE_BINARY_DIR})

add_custom_target(test
    DEPENDS unit_test c_test cpp_test style_test coverage_test)
