import sys, subprocess, getopt, os, re, shutil, argparse

COLOR_DEFAULT='\033[39m'
COLOR_YELLOW='\033[33m'
COLOR_GREEN='\033[32m'
COLOR_RED='\033[31m'

def die(msg):
	print("=== \t[", COLOR_RED, '-' , COLOR_DEFAULT, '] ', msg, sep='')
	sys.exit(1)

def info(msg):
	print("=== \t[", COLOR_GREEN, '+' , COLOR_DEFAULT, '] ', msg, sep='')

def runProcess(cmd):
	process = subprocess.run(cmd.split(' '), stdout=subprocess.PIPE, stderr=subprocess.PIPE)

	return process.returncode, process.stdout.decode('UTF-8'), process.stderr.decode('UTF-8')

def getMergeBranch():
	status, stdout, stderr = runProcess("git rev-parse --abbrev-ref HEAD")

	if status:
		die("Could not get current branch")

	mergeBranch = stdout.split('\n')[0]

	if mergeBranch == 'master':
		die("Could not merge master to itself")

	info(mergeBranch + " will be merged to master")

	return mergeBranch

def getTag():
	tag = ''
	try:
		tag = sys.argv[1]
	except:
		die("No tag found")
	
	info("Tag " + tag + " will be used")

	return tag

def updateBranch():
	cmd = 'git fetch && git pull && git merge master'
	status, stdout, stderr = runProcess('git fetch')

	if status:
		die('Could not fetch repository')
	info('Repository fetched')

	status, stdout, stderr = runProcess('git pull')

	if status:
		die('Could not pull current branch')
	info('Current branch pulled')

	status, stdout, stderr = runProcess('git merge master')

	if status:
		die('Could not merge current branch to master')
	info('master merged to current branch')

	info('Branches updated.')

def ensureModif():
	status, stdout, stderr = runProcess('Everything up-to-date')

	if status:
		die('Could not checkout to master')
		
		
def merge(mergeBranch, tag):
	status, stdout, stderr = runProcess('git checkout master')
	print(status, stdout, stderr)
	if status:
		die('Could not checkout to master')
	info('Checked out to master')

	status, stdout, stderr = runProcess('git merge --squash ' +mergeBranch)

	if status:
		die('Could not merge ' + mergeBranch + ' to master')
	info(mergeBranch + ' merged to master')

	status, stdout, stderr = runProcess('git tag -a ' + tag + '-m "Create tag ' + tag + '"')

	if status:
		die('Could not tag')
	info('Tagged')

	#status, stdout, stderr = runProcess('git push --follow-tags origin master')

	if status:
		die('Could not push')
	info('Pushed !')

ensureModif()

mergeBranch = getMergeBranch()
tag = getTag()

updateBranch()

merge(mergeBranch, tag)