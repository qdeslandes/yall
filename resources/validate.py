# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

import sys, subprocess, getopt, os, re, shutil

isError = False

COLOR_DEFAULT='\033[39m'
COLOR_YELLOW='\033[33m'
COLOR_GREEN='\033[32m'
COLOR_RED='\033[31m'

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
def prepare(argv):
	if len(argv) and argv[0] == '-w':
		workingDir = argv[1]
	else:
		workingDir = os.getcwd()

	buildDir = workingDir + "/build/validate"

	# Remove it first
	shutil.rmtree(buildDir, ignore_errors=True)
	os.makedirs(buildDir)
	
	return workingDir, buildDir

"""
	Analyzers
"""
def defaultAnalyzer(cmd, code, stdout, stderr):
	testResults(0 == code, cmd)

	if 0 != code:
		testError('Command failed.')

	return 0 == code

def valgrindAnalyzer(cmd, code, stdout, stderr):
	error = code != 0
	stats = {}

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
		elif '==         suppressed:' in line:
			val = int(list(filter(None, line.split(' ')))[2].replace(',', ''))
			if val:
				stats['suppressed'] = val

	statErrors = len(stats)
	
	testResults(not error and not statErrors, cmd)

	if error:
		testError('Valgrind detected and error.')

	if statErrors:
		for key in stats:
			testError(key.capitalize() + ' ' + str(stats[key]) + ' bytes.')

	return not error and not statErrors

def coverageAnalyzer(cmd, code, stdout, stderr):
	resultsLine = ''

	# Find the line 'Lines executed:' displayed line which contains the
	# covering percentage.
	for line in stdout.split('\n')[::-1]:
		if re.match('Lines executed:', line):
			resultsLine = line
			break
			
	coverage = float(re.split('[:% ]+', resultsLine)[2])

	testResults(0 == code and not coverage < 95.0, cmd)

	if coverage < 95.0:
		testError('Code coverage should be at least 95.0% (currently ', str(coverage), '%).')

	return 0 == code and not coverage < 95.0

def styleAnalyzer(cmd, code, stdout, stderr):
	lines = stdout.split('\n')

	warnings = 0
	errors = 0
	for line in lines:
		if re.match('WARNING', line):
			warnings += 1
		elif re.match('ERROR', line):
			errors += 1
	
	testResults(warnings or errors, cmd)

	if warnings or errors:
		testError('Warnings count : ' + str(warnings))
		testError('Errors count : ' + str(errors))
		testError('Run the test manually for more detailed output.')

	return not (warnings or errors)

"""
	Tests management
"""
def testSection(sectionName, tests):
	global isError
	print("=== \tTesting ", COLOR_GREEN, sectionName, COLOR_DEFAULT, " :", sep='')

	for cmd, analyzer in tests:
		if not test(cmd, analyzer):
			isError = True

def test(cmd, analyzer=defaultAnalyzer):
	returnValue = False
	result = subprocess.run(cmd.split(' '), stdout=subprocess.PIPE, stderr=subprocess.PIPE)

	try:
		returnValue = analyzer(cmd, result.returncode, result.stdout.decode('UTF-8'), result.stderr.decode('UTF-8'))
	except:
		pass

	return returnValue

def main(argv):
	print('=== Code validity checking for yall library.')
	print('=== Copyright (C) 2017 Quentin "Naccyde" Deslandes.')
	print('=== Redistribution and use of this file is allowed according to the terms of the MIT license.')

	workingDir, buildDir = prepare(argv)

	print('===')
	print('=== Working dir set to', workingDir)
	print('===')
	print('=== Starting tests :')

	# CMake, debug mode
	cmakeOptions = "-DCMAKE_BUILD_TYPE=Debug -DPROJECT-MISC_COVERAGE=On"
	debugSection = [
		['cmake -B' + buildDir + ' -H' + workingDir + ' ' + cmakeOptions, defaultAnalyzer],
		['make -C ' + buildDir + ' -j 9', defaultAnalyzer],
		['valgrind --error-exitcode=1337 ' + buildDir + '/tests/c/yall_c', valgrindAnalyzer],
		['valgrind --error-exitcode=1337 ' + buildDir + '/tests/cpp/yall_cpp', valgrindAnalyzer],
		['make -C ' + buildDir + ' unit', defaultAnalyzer],
		['make -C ' + buildDir + ' coverage', coverageAnalyzer]]
	testSection("Debug", debugSection)

	# CMake, release mode
	cmakeOptions = "-DCMAKE_BUILD_TYPE=Release -DPROJECT-MISC_COVERAGE=On"
	releaseSection = [
		['cmake -B' + buildDir + ' -H' + workingDir + ' ' + cmakeOptions, defaultAnalyzer],
		['make -C ' + buildDir + ' -j 9', defaultAnalyzer],
		['valgrind --error-exitcode=1337 ' + buildDir + '/tests/c/yall_c', valgrindAnalyzer],
		['valgrind --error-exitcode=1337 ' + buildDir + '/tests/cpp/yall_cpp', valgrindAnalyzer],
		['make -C ' + buildDir + ' unit', defaultAnalyzer],
		['make -C ' + buildDir + ' coverage', coverageAnalyzer]]
	testSection('Release', releaseSection)

	# Run checkstyle
	styleSection = [
		['make -C ' + buildDir + ' checkstyle', styleAnalyzer]]
	testSection('Style', styleSection)

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
