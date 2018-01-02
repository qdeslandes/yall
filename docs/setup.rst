*******************
Setup
*******************

Use `yall`
*******************

To use `yall`, you should add ``${YALL_INSTALL_FOLDER}/include`` to include directories of your compiler, and ``yall`` to the linked libraries. Depending of the install location of the library, you should have to add ``${YALL_INSTALL_FOLDER}/lib`` to the link directory.

If you use CMake, you can use CMake's ``find_package(yall)``. If the library is installed on Linux inside the default path (system path) then the CMake configuration file will be found, other set ``CMAKE_MODULES_PATH`` to the install location of ``yall``.

Initialize the library
*******************

``yall_init()`` is used to initialize the library. All other ``yall`` functions can't be used before initialization is done. This step allow to start the writing thread and setup default configuration. A counter is incremented in order to keep track of all the initializations done.

An object of type ``yall_error`` is returned, if the returned value is different than ``YALL_SUCCESS`` (from ``yall/error.h``), then the function failed and you can't use the library. You can get details about the error with a call to ``yall_strerror(returned_value)``.

Close the library
*******************

Once logging work is done, the library should be close in order to close the writing thread and free all the buffers. Two different closing functions are available which are :
* ``yall_close()`` : close the current instance of the library.
* ``yall_close_all()`` : close all the librarie's instances. 

``yall_close()`` should be called from shared / static libraries and ``yall_close_all()`` from executables. This avoid to close completely the library from a library as it is used from a base executable.
