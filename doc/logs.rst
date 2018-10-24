*******************
Log call
*******************

All the logging using ``yall`` is done with the logging macros. There is 7 logging level, each of them as an associated set of logging macros :

.. doxygenenum:: yall_log_level

The logging macro are then :
  * ``YALL_<log_level>(<subsystem>, <message>)`` : log the given message to the given subsystem (using its parameters). The log level to use in the macro call is the capitalized requested log level. The message parameters can be a ``printf()`` like format, followed by the modifier's content.
  * ``YALL_<log_level>_IF(<subsystem>, <expression>, <message>)`` : this macro has the same behaviour as the previous one, except it allow to log the message conditionally : if ``<expression>`` is evaluated to true, the message will be logged.


Logging macros
*******************

.. doxygendefine:: YALL_EMERG
.. doxygendefine:: YALL_ALERT
.. doxygendefine:: YALL_CRIT
.. doxygendefine:: YALL_ERR
.. doxygendefine:: YALL_WARNING
.. doxygendefine:: YALL_NOTICE
.. doxygendefine:: YALL_INFO
.. doxygendefine:: YALL_DEBUG

Conditional logging macros
**************************

.. doxygendefine:: YALL_EMERG_IF
.. doxygendefine:: YALL_ALERT_IF
.. doxygendefine:: YALL_CRIT_IF
.. doxygendefine:: YALL_ERR_IF
.. doxygendefine:: YALL_WARNING_IF
.. doxygendefine:: YALL_NOTICE_IF
.. doxygendefine:: YALL_INFO_IF
.. doxygendefine:: YALL_DEBUG_IF
