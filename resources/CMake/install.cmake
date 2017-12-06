# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

install(FILES README.md DESTINATION share/yall)
install(FILES changelog DESTINATION share/yall)

install(TARGETS yall_static yall_shared
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	CONFIGURATIONS Debug;Release)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ./ PATTERN "version.h.in" EXCLUDE)

if (WIN32)
	install(FILES external/lib/win32/msvc12/pthreadVC2.dll DESTINATION bin)
endif ()