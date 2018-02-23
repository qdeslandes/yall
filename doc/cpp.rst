*******************
C++
*******************

``yall`` handles C++ applications through ``Yall`` class defined in ``Yall.hpp``.

This class defines, as static, all the functions to manage the library :

.. code-block:: cpp

    Yall::init();
    Yall::setSubsystem(...)
    Yall::closeAll();
    ...

Configuration
*******************

To manage the configuration of the library, ``Yall`` provides a ``config`` method which returns ``YallConfig`` object. This object provides all the configuration functions defined in ``yall`` :

.. code-block:: cpp

    Yall::config().setStdHeaderTemplate(...);
    Yall::config().setTabWidth(...);
    Yall::config().resetCallHeaderTemplate(...);
    Yall::config().getTabWidth();
    ...

Logging macros
*******************

In C++, ``yall`` does not use ``printf()`` like format but C++ string streams, which leads to use ``<<`` operators :

.. code-block:: cpp

    VTS_EMERG("subsystem", "An error occured : " << string(e.what()));
    VTS_INFO("subsystem", "Current date is " << date());
    ...

Custom logging function
***********************

When using a custom function calling macro, the function prototype has to be ``void formatter(YallData &d, const void *args)``. Using class ``YallData`` allow to call :

* ``YallData::newLine(int indent)`` : create a new line on the call data, similar to ``yall_call_add_line(...)``, returns the new line as a ``std::stringstream``.
