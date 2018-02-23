*******************
Subsystem
*******************

Creation
*******************

Subsystems are the major feature of the library as they store different sets of logging parameters. Creating a subsystem is defining a set of parameter about how to handle log messages affected to this specific subsystem.

Subsystem creation is done with :

.. doxygenfunction:: yall_set_subsystem

If the subsystem name already exists, it will be updated with the given parameters.

Each subsystem can have, a parent from which it can inherits some parameters.

``log_level`` can have one of the following values :

.. doxygenenum:: yall_log_level

``output_type`` can have one of the following values :

.. doxygenenum:: yall_output_type

If ``output_type`` is ``yall_file_output``, then ``output_file`` can be set to the output file name, or to ``NULL`` to use the parent's output file.

Destruction
*******************

Subsystems are destroyed during library deinitialization. Currently, their is no way to specifically destroy a subsystem during execution.
