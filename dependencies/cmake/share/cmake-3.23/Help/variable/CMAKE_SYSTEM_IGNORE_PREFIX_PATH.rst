CMAKE_SYSTEM_IGNORE_PREFIX_PATH
-------------------------------

.. versionadded:: 3.23

:ref:`Semicolon-separated list <CMake Language Lists>` of prefixes to be
*ignored* by the :command:`find_program`, :command:`find_library`,
:command:`find_file`, :command:`find_path`, and :command:`find_package`
commands.  This is useful in cross-compiling environments where some
system directories contain incompatible but possibly linkable libraries.
For example, on cross-compiled cluster environments, this allows a user
to ignore directories containing libraries meant for the front-end machine.

By default this contains a list of directories containing incompatible
binaries for the host system.  See the :variable:`CMAKE_IGNORE_PREFIX_PATH`
variable that is intended to be set by the project and/or the end user.

See also the :variable:`CMAKE_SYSTEM_PREFIX_PATH`,
:variable:`CMAKE_SYSTEM_LIBRARY_PATH`, :variable:`CMAKE_SYSTEM_INCLUDE_PATH`,
and :variable:`CMAKE_SYSTEM_PROGRAM_PATH` variables.
