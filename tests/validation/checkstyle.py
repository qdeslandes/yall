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

    parser = argparse.ArgumentParser(description='Check yall sources coverage')
    parser.add_argument('--sourcesDir', required=True, help='Sources directory')
    args = parser.parse_args()

    c = YallCommand()
    c.cmd = args.sourcesDir + '/tests/validation/checkstyle.sh ' + args.sourcesDir
    c.env = customEnv
    c.cwd = args.sourcesDir
    c.analyzer = styleAnalyzer

    return analyze(c)

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))