# 
# Run checkpatch script for coding guidelines
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

mkdir -p build/checkstyle

if [ ! -f ./build/checkstyle/checkpatch.pl ]; then
    # Download script and create files only if they do no exists
    wget https://raw.githubusercontent.com/torvalds/linux/master/scripts/checkpatch.pl -O ./build/checkstyle/checkpatch.pl
    chmod +x ./build/checkstyle/checkpatch.pl
    touch ./build/checkstyle/spelling.txt
    touch ./build/checkstyle/const_structs.checkpatch
fi

for file in $(find src include -regex '.*\.\(c\|h\)')
do
    case "$file" in
        *cpp*)
	    continue
	    ;;
        *msvc_defines.h)
	    continue
	    ;;
    esac

    ./build/checkstyle/checkpatch.pl -q \
        --ignore CONST_STRUCT,INITIALISED_STATIC,SPACING,GLOBAL_INITIALISERS,NEW_TYPEDEFS,USE_FUNC \
        --no-tree \
        -f $file
done