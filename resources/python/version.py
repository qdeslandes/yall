#!/bin/python3

# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

import sys
import os
import requests
import json
import argparse
import re
from distutils.version import StrictVersion

class Release:
    def __init__(self, gitlabToken, gitTag, commitSha, projectId, packagesDir='./'):
        self.gitlabToken = gitlabToken
        self.gitTag = gitTag
        self.commitSha = commitSha
        self.projectId = projectId
        self.packagesDir = packagesDir
        self.description = ''

        self.check()

    def check(self):
        print('\tSearching artifacts...')
        self.findArtifacts()

    def prepare(self):
        self.uploadArtifacts()
        self.generateTagDescription()

    def create(self):
        print('Creating release...')
        data = { 'tag_name' : self.gitTag, 'ref' : self.commitSha, 'release_description' : self.description }

        self.gitlabPost('/projects/' + self.projectId + '/repository/tags', data=data)

    def findArtifacts(self):
        self.artifacts = [Artifact(f, self.packagesDir + '/' + f) for f in os.listdir(self.packagesDir)]

        if not len(self.artifacts):
            print('\t\tNo artifact found')
            return

        for artifact in self.artifacts:
            print('\t\t' + artifact.name)
    
    def generateTagDescription(self):
        print('\tGenerating description')
        self.description = '# **Release ' + self.gitTag + '**\n\n'

        self.description += '### Changes\n\n' + self.getCommitMessage() + '\n\n'

        self.description += '### Artifacts\n\n'
        for artifact in self.artifacts:
            self.description += artifact.markdown + '\n\n'

    def getCommitMessage(self):
        return self.gitlabGet('/projects/' + self.projectId + '/repository/commits/' + self.commitSha)['message']

    def uploadArtifacts(self):
        for artifact in self.artifacts:
            print('\tUploading ' + artifact.name + '...')
            file = { 'file' : (artifact.name, open(artifact.path, 'rb'))}

            jsonData = self.gitlabPost('/projects/' + self.projectId + '/uploads', file=file)

            artifact.markdown = jsonData['markdown']
            print('\t\t' + artifact.markdown)


    def gitlabPost(self, endpoint, data=None, file=None):
        url = 'https://gitlab.com/api/v4' + endpoint
        headers = { 'PRIVATE-TOKEN' : self.gitlabToken }

        re = requests.post(url, headers=headers, data=data, files=file)

        if re.status_code < 200 or 300 <= re.status_code:
            print('ERROR : Status ' + str(re.status_code) + ' on ' + endpoint + ' with ' + re.text)
            sys.exit(1)

        return json.loads(re.text)


def gitlabGet(endpoint):
    url = 'https://gitlab.com/api/v4' + endpoint

    re = requests.get(url)

    if 200 != re.status_code:
        print('ERROR : Status ' + str(re.status_code) + ' on ' + endpoint)
        sys.exit(1)

    return json.loads(re.text)

def computeBranchPrefix(title):
    prefix = ''
    m = re.search('\'(.*)\/.*\'', title)

    try:
        prefix = m.group(1)
    except:
        print('ERROR : could not find name in commit message "' + title + '"')
        sys.exit(1)

    return prefix

def computeNextVersion(branchPrefix, lastVersion):
    lastVersion = list(map(int, lastVersion.split('.')))

    if 'major_feature' == branchPrefix:
        lastVersion = [ lastVersion[0] + 1, 0, 0 ]
    elif 'minor_feature' == branchPrefix:
        lastVersion = [ lastVersion[0], lastVersion[1] + 1, 0 ]
    else:
        lastVersion = [ lastVersion[0], lastVersion[1], lastVersion[2] + 1 ]

    return lastVersion

def writeNextVersion(outputFolder, version):
    with open(outputFolder + '/version', 'w') as f:
        f.write(str(version[0]) + '.' + str(version[1]) + '.' + str(version[2]))

    with open(outputFolder + '/major', 'w') as f:
        f.write(str(version[0]))

    with open(outputFolder + '/minor', 'w') as f:
        f.write(str(version[1]))

    with open(outputFolder + '/patch', 'w') as f:
        f.write(str(version[2]))


def main():
    parser = argparse.ArgumentParser(description='Script used to push a Gitlab release')
    parser.add_argument('-p', '--project-id', required=True, help='Project ID')
    parser.add_argument('-c', '--commit-sha', required=True, help='Commit SHA')
    parser.add_argument('-o', '--output-folder', required=True, help='Folder to write next tag infos')
    args = parser.parse_args()

    data = gitlabGet('/projects/' + args.project_id + '/repository/tags')
    versions = [ v['name'] for v in data ]
    versions.sort(key=StrictVersion)
    lastVersion = versions[-1]

    title = gitlabGet('/projects/' + args.project_id + '/repository/commits/' + args.commit_sha)['title']
    branchPrefix = computeBranchPrefix(title)

    version = computeNextVersion(branchPrefix, lastVersion)
    versionStr = str(version[0]) + '.' + str(version[1]) + '.' + str(version[2])
    print('From ' + lastVersion + ' to ' + versionStr)
    writeNextVersion(args.output_folder, version)

main()
