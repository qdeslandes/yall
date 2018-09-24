*******************
Debugging
*******************

``yall`` defines some debugging function, useful to avoid messing with the susbystems tree or to have more informations about an error.

First, debug mode should be enabled :

.. doxygenfunction:: yall_enable_debug

The given subsystem must exists before using it as debug subsystem. Once debug mode activated, ``yall`` will write log message (using this subsystem) during its use.

To check debug mode status :

.. doxygenfunction:: yall_is_debug

If you need to disable debug mode (it does not delete the debug subsystem) : 

.. doxygenfunction:: yall_disable_debug

Finally, it is possible to display the current subsystems tree with :

.. doxygenfunction:: yall_show_subsystems_tree
