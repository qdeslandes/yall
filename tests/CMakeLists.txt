# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_subdirectory(real)
add_subdirectory(cpp)

# Unit testing can't be done on MSVC 12 because Criterion is not available
if (NOT WIN32 OR NOT MSVC_VERSION EQUAL 1800)
	add_subdirectory(unit)
endif ()
