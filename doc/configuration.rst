*******************
Configuration
*******************

The behaviour of the library can be configured through a set of functions. The currently customizable parameters are the following.

Each configurable parameter has a *setter*, *resetter* and *getter*.

Standard header
*******************

The standard header is the prefix used in front of each log message while calling a simple logging macro like ``YALL_ERROR(...)``. The format of the header is in ``printf()`` style. Available modifiers are :

* ``%s`` : replace the modifier with the subsystem's name.
* ``%l`` : replace the modifier with the log's level.
* ``%f`` : replace the modifier with the calling function's name.
* ``%F`` : replace the modifier with the current filename.
* ``%L`` : replace the modifier with the current line.
* ``%d`` : replace the modifier with the date time of the log. The format of the date can't be changed, it is : ``YYYY-MM-DD HH:MM:SS``.

.. doxygenfunction:: yall_config_set_std_header_template
.. doxygenfunction:: yall_config_reset_std_header_template
.. doxygenfunction:: yall_config_get_std_header_template

Call header
*******************

.. doxygenfunction:: yall_config_set_call_header_template
.. doxygenfunction:: yall_config_reset_call_header_template
.. doxygenfunction:: yall_config_get_call_header_template

Tabulation width
*******************

.. doxygenfunction:: yall_config_set_tab_width
.. doxygenfunction:: yall_config_reset_tab_width
.. doxygenfunction:: yall_config_get_tab_width
