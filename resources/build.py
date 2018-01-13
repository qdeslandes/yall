# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

import sys, subprocess, getopt, os, re, shutil, argparse

isError = False
customEnv = []
fullOutput = False

COLOR_DEFAULT='\033[39m'
COLOR_YELLOW='\033[33m'
COLOR_GREEN='\033[32m'
COLOR_RED='\033[31m'

class TestType:
	VALGRIND = 1
	UNIT = 2
	COVERAGE = 3
	STYLE = 4

"""
	Message formatting
"""
def testResults(status, cmd):
	color = COLOR_GREEN if status else COLOR_RED
	symbol = '+' if status else '-'
	print("=== \t\t[", color, symbol, COLOR_DEFAULT, '] ', cmd, sep='')

def testError(msg):
	print('=== \t\t\t', COLOR_RED, '-> ', msg, COLOR_DEFAULT, sep='')

"""
	Setup
"""
def prepare(build):
	workingDir = os.getcwd()
	buildDir = workingDir

	if build:
		buildDir = workingDir + "/validate"

		# Remove it first
		shutil.rmtree(buildDir, ignore_errors=True)
		os.makedirs(buildDir)

	return workingDir, buildDir

"""
	Analyzers
"""
def defaultAnalyzer(cmd, code, stdout, stderr):
	if fullOutput:
		print(stderr)

	testResults(0 == code, cmd)

	if 0 != code:
		testError('Run the test manually for more detailed output.')

	return 0 == code

def gccAnalyzer(cmd, code, stdout, stderr):
	if fullOutput:
		print(stderr)

	lines = stderr.split('\n')

	warnings = 0
	errors = 0
	notes = 0

	for line in lines:
		if ': note:' in line:
			notes += 1
		elif ': warning:' in line:
			warnings += 1
		elif ': error:' in line:
			errors += 1

	testResults(not (notes or warnings or errors), cmd)

	if notes:
		testError(str(notes) + ' note(s).')
	if warnings:
		testError(str(warnings) + ' warning(s).')
	if errors:
		testError(str(errors) + ' error(s).')

	if notes or warnings or errors:
		testError('Run the test manually for more detailed output.')

	return not (notes or warnings or errors)

def valgrindAnalyzer(cmd, code, stdout, stderr):
	if fullOutput:
		print(stderr)

	error = code != 0
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

	statErrors = len(stats)

	testResults(not error and not statErrors, cmd)

	if error:
		testError('Valgrind detected and error.')

	if statErrors:
		for key in stats:
			testError(key.capitalize() + ' ' + str(stats[key]) + ' bytes.')

	return not error and not statErrors

def unitAnalyzer(cmd, code, stdout, stderr):
	if fullOutput:
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

	testResults(0 == code and 0 == fail and 0 == crash, cmd)

	if 0 != fail:
		testError(str(fail) + ' failed.')
	if 0 != crash:
		testError(str(crash) + ' crashed.')
	if 0 != code and 0 != fail and 0 != crash:
		testError('Run the test manually for more detailed output.')

	return 0 == code and 0 == fail and 0 == crash

def coverageAnalyzer(cmd, code, stdout, stderr):
	if fullOutput:
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

	testResults(0 == code and coverage > 95.0, cmd)

	if coverage < 95.0:
		testError('Code coverage should be at least 95.0% (currently ' + str(coverage) + '%).')
	if 0 != code:
		testError('Run the test manually for more detailed output.')

	return 0 == code and not coverage < 95.0

def styleAnalyzer(cmd, code, stdout, stderr):
	if fullOutput:
		print(stderr)

	lines = stdout.split('\n')

	warnings = 0
	errors = 0
	for line in lines:
		if re.match('WARNING', line):
			warnings += 1
		elif re.match('ERROR', line):
			errors += 1

	testResults(not (0 != code or warnings or errors), cmd)

	if warnings:
		testError(str(warnings) + ' warning(s)')
	if errors:
		testError(str(errors) + ' error(s)')
	if 0 != code or warnings or errors:
		testError('Run the test manually for more detailed output')

	return not (0 != code or warnings or errors)

"""
	Tests management
"""
def runTests(tests):
	global isError
	for cmd, analyzer in tests:
		if not test(cmd, analyzer):
			isError = True

def test(cmd, analyzer=defaultAnalyzer):
	returnValue = False
	result = subprocess.run(cmd.split(' '), stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=customEnv)

	returnValue = analyzer(cmd, result.returncode, result.stdout.decode('UTF-8'), result.stderr.decode('UTF-8'))

	print(cmd, "returned", returnValue)
	return returnValue

def main(argv):
	global customEnv
	global fullOutput

	customEnv = os.environ.copy()
	customEnv["LC_ALL"] = "C"

	parser = argparse.ArgumentParser(description='Validate yall library sources')
	parser.add_argument('--sourcesDir', required=True, help='Sources directory')
	parser.add_argument('--buildDir', required=True, help='Build directory')
	parser.add_argument('-w', '--wrapper', action='store_true', help='Use SonarQube build wrapper')
	parser.add_argument('-v', '--verbose', action='store_true', help='Verbose output')
	args = parser.parse_args()

	fullOutput = args.verbose
	buildPrefix = ""
	if args.wrapper:
		buildPrefix = 'build-wrapper-linux-x86-64 --out-dir ' + args.buildDir + '/bw_output '

	print('=== Code validity checking for yall library.')
	print('=== Copyright (C) 2017 Quentin "Naccyde" Deslandes.')
	print('=== Redistribution and use of this file is allowed according to the terms of the MIT license.')

	print('===')
	print('=== Working dir set to', args.buildDir)
	print('===')
	print('=== Starting tests :')

	print('===\t[', COLOR_YELLOW, '.', COLOR_DEFAULT, '] Release :', sep='')
	testsRelease = [
		['cmake -B' + args.buildDir + ' -H' + args.sourcesDir + ' -DCMAKE_BUILD_TYPE=Release', defaultAnalyzer],
		['make -C ' + args.buildDir + ' clean', defaultAnalyzer],
		[buildPrefix + 'make -C ' + args.buildDir + ' -j 9', gccAnalyzer],
		['valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1337 ' + args.buildDir + '/yall_c', valgrindAnalyzer],
		['valgrind --suppressions=' + args.sourcesDir + '/resources/valgrind_cpp.supp --leak-check=full --show-leak-kinds=all --error-exitcode=1337 ' + args.buildDir + '/yall_cpp', valgrindAnalyzer],
		[args.buildDir + '/yall_unit', unitAnalyzer],
		['make -C ' + args.buildDir + ' coverage', coverageAnalyzer],
		['make -C ' + args.buildDir + ' doxygen_doc', defaultAnalyzer],
		['make -C ' + args.buildDir + ' package', defaultAnalyzer],
		['make -C ' + args.buildDir + ' checkstyle', styleAnalyzer]]

	runTests(testsRelease)

	print('===\t[', COLOR_YELLOW, '.', COLOR_DEFAULT, '] Debug :', sep='')
	testsDebug = [
		['cmake -B' + args.buildDir + ' -H' + args.sourcesDir + ' -DCMAKE_BUILD_TYPE=Debug', defaultAnalyzer],
		['make -C ' + args.buildDir + ' clean', defaultAnalyzer],
		['make -C ' + args.buildDir + ' -j 9', gccAnalyzer],
		['make -C ' + args.buildDir + ' package', defaultAnalyzer]]

	runTests(testsDebug)

	# Results
	print('=== ')

	if not isError:
		print('=== ', COLOR_GREEN, 'No error found.', COLOR_DEFAULT, sep='')
	else:
		print('=== ', COLOR_RED, 'Error(s) found, fix before commiting.', COLOR_DEFAULT, sep='')

	print('=== ')

	return 1 if isError else 0

if __name__ == "__main__":
	sys.exit(main(sys.argv[1:]))
