#!/bin/sh

# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

# This script is used to generate GCOV anaylize files.
# Param : absolute sources directory
# Param : build directory
# It requires only 1 parameter : build folder.
# It will then run gcov command from build/coverage folder, and search for
# .gcda files inside the build folder.
# This script must be launched from the top level directory of the project.

SOURCES_PATH=$1
BUILD_PATH=$2

mkdir -pv $BUILD_PATH/coverage && cd $_

gcov -abcfu -s $SOURCES_PATH `find $BUILD_PATH -name "*.gcda"`
