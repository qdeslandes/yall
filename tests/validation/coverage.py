#!/bin/python3

# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

import sys, os, argparse, subprocess
import errno

from helper import *

def main(argv):
    customEnv = os.environ.copy()
    customEnv["LC_ALL"] = "C"

    parser = argparse.ArgumentParser(description='Check yall sources coverage')
    parser.add_argument('--sourcesDir', required=True, help='Sources directory')
    parser.add_argument('--outDir', required=True, help='GCOV files output directory')
    parser.add_argument('--gcnoDir', required=True, help='GCNO files directory')
    args = parser.parse_args()
    
    try:
        os.makedirs(args.outDir)
    except Exception as e:
        if e.errno != errno.EEXIST:
            exit(e.errno)

    c = YallCommand()
    c.cmd = 'gcov -abcfu `find ' + args.gcnoDir + ' -name "*.gcno"`'
    c.env = customEnv
    c.cwd = args.outDir
    c.analyzer = coverageAnalyzer

    return analyze(c)

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
