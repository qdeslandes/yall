# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

# 
# Run checkpatch script for coding guidelines
#
# param : top level directory of the project
#
# Disabled options are :
#    * CONST_STRUCT : as no structure *MUST* be used as const
#    * INITIALISED_STATIC : let me initialize my static variable.
#    * SPACING : because "if (! var)" is better than "if (!var)"
#    * GLOBAL_INITIALISERS : same as INITIALISED_STATIC
#    * NEW_TYPEDEFS : typedef are used to obsfuscate struct internals to user
#    * USE_FUNC : __func__ is use on Windows, which leads to a false positive
#
# This script should be run from the root of the repository
#

ROOT_DIR=$@

for file in $(find $ROOT_DIR/src $ROOT_DIR/include -regex '.*\.\(c\|h\)')
do
    case "$file" in
        *cpp*)
	    continue
	    ;;
        *msvc_defines.h)
	    continue
	    ;;
    esac

    $ROOT_DIR/tests/validation/checkpatch.pl -q \
        --ignore CONST_STRUCT,INITIALISED_STATIC,SPACING,GLOBAL_INITIALISERS,NEW_TYPEDEFS,USE_FUNC \
        --no-tree \
        -f $file
done