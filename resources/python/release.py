#!/bin/python3

# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

import sys
import os
import requests
import json
import argparse

class Artifact:
    def __init__(self, name, path):
        self.name = name
        self.path = path
        self.markdown = ''

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

    def gitlabGet(self, endpoint):
        url = 'https://gitlab.com/api/v4' + endpoint
        headers = { 'PRIVATE-TOKEN' : self.gitlabToken }

        re = requests.get(url, headers=headers)

        if 200 != re.status_code:
            print('ERROR : Status ' + str(re.status_code) + ' on ' + endpoint)
            sys.exit(1)

        return json.loads(re.text)

    def gitlabPost(self, endpoint, data=None, file=None):
        url = 'https://gitlab.com/api/v4' + endpoint
        headers = { 'PRIVATE-TOKEN' : self.gitlabToken }

        re = requests.post(url, headers=headers, data=data, files=file)

        if re.status_code < 200 or 300 <= re.status_code:
            print('ERROR : Status ' + str(re.status_code) + ' on ' + endpoint + ' with ' + re.text)
            sys.exit(1)

        return json.loads(re.text)

def main():
    parser = argparse.ArgumentParser(description='Script used to push a Gitlab release')
    parser.add_argument('-k', '--gitlab-token', required=True, help='Gitlab token')
    parser.add_argument('-t', '--git-tag', required=True, help='Git tag')
    parser.add_argument('-i', '--project-id', required=True, help='Gitlab project ID')
    parser.add_argument('-p', '--packages-dir', required=True, help='Packages directory')
    parser.add_argument('-c', '--commit-sha', required=True, help='Commit SHA')
    args = parser.parse_args()

    print("=== Gitlab release creation ===")
    r = Release(args.gitlab_token, args.git_tag, args.commit_sha, args.project_id, args.packages_dir)
    r.prepare()
    r.create()

    print('RELEASED !')

main()
