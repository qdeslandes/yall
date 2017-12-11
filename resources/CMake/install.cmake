# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.
install(FILES README.md DESTINATION share/yall COMPONENT all)

install(FILES changelog DESTINATION share/yall COMPONENT dev)

install(TARGETS yall_static yall_shared
	RUNTIME DESTINATION bin COMPONENT all
	ARCHIVE DESTINATION lib COMPONENT all
	LIBRARY DESTINATION lib COMPONENT all)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ./ COMPONENT dev PATTERN "version.h.in" EXCLUDE)

if (WIN32)
	install(FILES external/lib/win32/msvc12/pthreadVC2.dll DESTINATION bin COMPONENT all)
endif ()
