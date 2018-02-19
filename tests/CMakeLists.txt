# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_subdirectory(c)
add_subdirectory(cpp)

if (UNIX OR MSVC_VERSION EQUAL 1900)
    add_subdirectory(unit)
endif ()
