# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (PROJECT_REAL_TESTS)
	add_subdirectory(real)
endif ()

if (PROJECT_CPP_TESTS)
	add_subdirectory(cpp)
endif ()

# Unit testing can't be done on MSVC 12 because Criterion is not available
if ((NOT WIN32 OR NOT MSVC_VERSION EQUAL 1800) AND PROJECT_UNIT_TESTS)
	add_subdirectory(unit)
endif ()
