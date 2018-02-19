#!/bin/python3

# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

import sys, os, argparse, subprocess, re

COLOR_DEFAULT='\033[39m'
COLOR_YELLOW='\033[33m'
COLOR_GREEN='\033[32m'
COLOR_RED='\033[31m'

def testResults(success, cmd, successMsg, errorMsg):
    color = COLOR_GREEN if success else COLOR_RED
    resInfo = 'SUCCESS' if success else 'FAILURE'
    print(color, resInfo, COLOR_DEFAULT, ' -> ', cmd, sep='')

    if success:
        print('\t' + successMsg)
    else:
        print('\t' + errorMsg)

    return success

"""
    Analyzers
"""
def defaultAnalyzer(cmd, code, stdout, stderr):
    print(stderr)
    print("Default")
    #testResults(0 == code, cmd)

    if 0 != code:
        testError('Run the test manually for more detailed output.')

    return 0 == code

def coverageAnalyzer(cmd, code, stdout, stderr):
    print("hihi")
    print(stdout)
    print(stderr)

    resultsLine = ''
    coverage = 0.0

    # Find the line 'Lines executed:' displayed line which contains the
    # covering percentage.
    for line in stdout.split('\n')[::-1]:
        if re.match('Lines executed:', line):
            resultsLine = line
            break

    try:
        coverage = float(re.split('[:% ]+', resultsLine)[2])
    except:
        coverage = 0.0

    success = 0 == code and coverage > 95.0

    errorMsg = 'Code coverage should be at least 95.0% (currently ' + str(coverage) + '%).'
    successMsg = 'Code coverage is above 95.0% (currently ' + str(coverage) + '%).'

    return testResults(success, cmd, successMsg, errorMsg)

def styleAnalyzer(cmd, code, stdout, stderr):
    print(stdout)
    print(stderr)

    lines = stdout.split('\n')

    warnings = 0
    errors = 0
    for line in lines:
        if re.match('WARNING', line):
            warnings += 1
        elif re.match('ERROR', line):
            errors += 1

    success = code == 0 and (warnings + errors) == 0

    errorMsg = 'Checkstyle failed : ' + str(warnings) + ' warnings, ' + str(errors) + ' errors.'
    successMsg = 'Checkstyle passed.'

    return testResults(success, cmd, successMsg, errorMsg)


def valgrindAnalyzer(cmd, code, stdout, stderr):
    print(stdout)
    print(stderr)
    stats = {}

    # Do not count suppressed error, as it comes from suppression files

    for line in stderr.split('\n'):
        if re.match('total heap usage:', line):
            tokens = line.split(' ')
            unfreed = int(tokens[4]) - int(tokens[6])
        elif '==    definitely lost:' in line:
            val = int(list(filter(None, line.split(' ')))[3].replace(',', ''))
            if val:
                stats['definitely lost'] = val
        elif '==    indirectly lost:' in line:
            val = int(list(filter(None, line.split(' ')))[3].replace(',', ''))
            if val:
                stats['indirectly lost'] = val
        elif '==      possibly lost:' in line:
            val = int(list(filter(None, line.split(' ')))[3].replace(',', ''))
            if val:
                stats['possibly lost'] = val
        elif '==    still reachable:' in line:
            val = int(list(filter(None, line.split(' ')))[3].replace(',', ''))
            if val:
                stats['still reachable'] = val

    success = 0 == code and 0 == len(stats)

    resume = ''
    for key in stats:
        resume += key.capitalize() + ' ' + str(stats[key]) + ' bytes, '

    resume += '.'

    errorMsg = 'Valgrind test failed : ' + resume
    successMsg = 'Valgrind test success.'

    return testResults(success, cmd, successMsg, errorMsg)

def unitAnalyzer(cmd, code, stdout, stderr):
    print(stdout)
    print(stderr)

    fail = 0
    crash = 0
    synthesisLine = ''
    for line in stderr.split('\n'):
        if 'Synthesis:' in line:
            synthesisLine = line

    ansi_escape = re.compile(r'(\x9B|\x1B\[)[0-?]*[ -/]*[@-~]')
    if '' != synthesisLine:
        for token in synthesisLine.split('|'):
            l = token.split(':')
            if 2 == len(l):
                val = int(ansi_escape.sub('', l[1]))

                if 'Failing' in l[0]:
                    fail = val
                elif 'Crashing' in l[0]:
                    crash = val

    success = 0 == code and 0 == (fail + crash)
    errorMsg = 'Unit tests failed : ' + str(fail) + ' tests failed, ' + str(crash) + ' tests crashed.'
    successMsg = 'Unit tests success.'

    return testResults(success, cmd, successMsg, errorMsg)

class YallCommand:
    def __init__(self):
        self.cmd = 'echo "No command defined"'
        self.env = None
        self.cwd = None
        self.analyzer = defaultAnalyzer

def analyze(yallCmd):
    result = subprocess.run(yallCmd.cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=yallCmd.env, cwd=yallCmd.cwd, shell=True)

    # Reverse the analyzer returned value as outside this module, return values are used normally (1 is then an error)
    return not yallCmd.analyzer(yallCmd.cmd, result.returncode, result.stdout.decode('UTF-8'), result.stderr.decode('UTF-8'))