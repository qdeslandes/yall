# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#[[
	Yall objects compilation
#]]

file(GLOB_RECURSE YALL_SRCS ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/include/*.h)

# For more infos about the used flags :
#	* https://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c
#	* https://kristerw.blogspot.fr/2017/09/useful-gcc-warning-options-not-enabled.html
# Compile options
set(_PVT_OPT -Wall -Wextra -Wconversion -ftrapv -Wfloat-equal -Wundef
    -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes
    -Wwrite-strings -Waggregate-return -Wuninitialized
    -Wduplicated-cond -Wlogical-op -Wnull-dereference -Wdouble-promotion
    -fvisibility=hidden -fPIC)
set(_PVT_OPT_DEBUG  -O0 -g)
set(_PVT_OPT_RELEASE -O3 -Werror)

macro(createBenchmark name) 
    add_executable(yall_benchmark_${name} ${YALL_SRCS} ${name}.c)

    target_compile_options(yall_benchmark_${name}
        PRIVATE
            ${_PVT_OPT}
            $<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
            $<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

    target_compile_definitions(yall_benchmark_${name}
        PRIVATE ${_PVT_DEF})

    target_include_directories(yall_benchmark_${name}
        PRIVATE
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
            ${CMAKE_BINARY_DIR}/generated_headers)

    target_link_libraries(yall_benchmark_${name}
        PRIVATE
            pthread::pthread
            jansson::jansson)
endmacro(createBenchmark)

createBenchmark(call_add_message)
