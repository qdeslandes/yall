# Convert 8 spaces to tabs
for file in $(find src include -regex '.*\.\(c\|h\)')
do
    perl -p -i -e 's/        /\t/g' $file
done

# Run checkpatch script for coding guidelines
# Disabled options are :
#    * CONST_STRUCT : as no structure *MUST* be used as const
#    * INITIALISED_STATIC : let me initialize my static variable.
#    * SPACING : because "if (! var)" is better than "if (!var)"
#    * GLOBAL_INITIALISERS : same as INITIALISED_STATIC
#    * NEW_TYPEDEFS : typedef are used to obsfuscate struct internals to user
#    * USE_FUNC : __func__ is use on Windows, which leads to a false positive
for file in $(find src include -regex '.*\.\(c\|h\)')
do
    ./resources/checkpatch.pl -q --ignore CONST_STRUCT,INITIALISED_STATIC,SPACING,GLOBAL_INITIALISERS,NEW_TYPEDEFS,USE_FUNC --no-tree \
         -f $file
done