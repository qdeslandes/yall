*******************
Call
*******************

During logging process, it is possible to call a custom logging function. This allow to format a multilines log message the way you want.

Custom logging function
***********************

To use this feature, first you have to create a function with the following prototype : ``void formatter(yall_call_data *d, const void *args)``.

On logging time, this function will be called with a ``yall_call_data`` parameter, which is used to store user's generated log message, and ``args`` which are custom argument given during logging macro call.

Inside this logging function, the following functions can be called to manipulate the ``yall_call_data`` parameter :

.. doxygenfunction:: yall_call_set_header
.. doxygenfunction:: yall_call_add_line

Logging macros
*******************

.. doxygendefine:: YALL_CALL_EMERG
.. doxygendefine:: YALL_CALL_ALERT
.. doxygendefine:: YALL_CALL_CRIT
.. doxygendefine:: YALL_CALL_ERR
.. doxygendefine:: YALL_CALL_WARNING
.. doxygendefine:: YALL_CALL_NOTICE
.. doxygendefine:: YALL_CALL_INFO
.. doxygendefine:: YALL_CALL_DEBUG

Conditional logging macros
**************************

.. doxygendefine:: YALL_CALL_EMERG_IF
.. doxygendefine:: YALL_CALL_ALERT_IF
.. doxygendefine:: YALL_CALL_CRIT_IF
.. doxygendefine:: YALL_CALL_ERR_IF
.. doxygendefine:: YALL_CALL_WARNING_IF
.. doxygendefine:: YALL_CALL_NOTICE_IF
.. doxygendefine:: YALL_CALL_INFO_IF
.. doxygendefine:: YALL_CALL_DEBUG_IF
