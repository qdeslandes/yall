#!/bin/python3

# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

import sys, os, argparse, subprocess
import errno

# UGLY HACK
sys.path.insert(0, './resources/python')

from helper import *

def main(argv):
    customEnv = os.environ.copy()
    customEnv["LC_ALL"] = "C"

    parser = argparse.ArgumentParser(description='Run Valgrind on yall test binaries and analyze output')
    parser.add_argument('--binary', required=True, help='Binary to run with Valgrind')
    args = parser.parse_args()

    c = YallCommand()
    c.cmd = 'valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1337 ' + args.binary
    c.env = customEnv
    c.analyzer = valgrindAnalyzer

    return analyze(c)

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))