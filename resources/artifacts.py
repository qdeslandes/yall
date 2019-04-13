#!/bin/python3

# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

import sys
import os
import requests
import json
import argparse
import subprocess
import fnmatch

owner = 'naccyde'
repo = 'yall'
prefixPath = 'build/out/packages'
        
requiredDistros = {
    'deb' : {
        'ubuntu' : [ 'xenial', 'yakkety', 'zesty', 'artful', 'bionic' ],
        'debian' : [ 'jessie', 'wheezy', 'stretch', 'buster' ]
    },
    'rpm' : {
        'fedora' : [ '25', '26', '27', '28' ]
    }
}

def findDistroIds(requiredDistros, pcDistributions):
    distrosPackages = {}

    for pcExt in pcDistributions:
        if not pcExt in requiredDistros:
            continue

        distrosPackages[pcExt] = { 'ids' : [], 'filename' : [] }

        for pcDistro in pcDistributions[pcExt]:
            if not pcDistro['index_name'] in requiredDistros[pcExt]:
                continue

            versions = requiredDistros[pcExt][pcDistro['index_name']]
            
            for pcVersion in pcDistro['versions']:
                if not pcVersion['index_name'] in versions:
                    continue
                
                distrosPackages[pcExt]['ids'].append(pcVersion['id'])
    
    return distrosPackages

def getArtefacts(folder, extensionFilter):
    files = [f for f in os.listdir(folder)]

    return fnmatch.filter(files, extensionFilter)

class HttpApi:
    def isStatusValid(self, statusCode):
        return 200 <= statusCode <= 299

    def get(self, url, headers={}):
        re = requests.get(url, headers=headers)

        return re.status_code, re.text
    
    def post(self, url, headers={}, data={}, files={}):
        re = requests.post(url, headers=headers, json=data, files=files)

        return re.status_code, re.text

class PackageCloudApi(HttpApi):
    def __init__(self, owner, repo, token):
        self.owner = owner
        self.repo = repo
        self.token = token

        self.apiUrl = 'https://{}:@packagecloud.io/api/v1'.format(token)

    def getDistributions(self):
        url = self.apiUrl + '/distributions.json'

        status, text = self.get(url)

        return status, json.loads(text)
    
    def uploadPackage(self, distroId, filename):
        url = self.apiUrl + '/repos/{}/{}/packages.json'.format(self.owner, self.repo)

        file = {
            'package[distro_version_id]': (None, str(distroId)),
            'package[package_file]': (filename, open(prefixPath + '/' + filename, 'rb')),
        }

        status, text = self.post(url, files=file)

        return status, json.loads(text)

    def uploadPackages(self, distrosPackages={}):
        for distro in distrosPackages:
            for distroId in distrosPackages[distro]['ids']:
                for filename in distrosPackages[distro]['filename']:
                    print('\t\t[+] Uploading', filename, 'to', distroId)
                    status, text = self.uploadPackage(distroId, filename)

                    if not 200 <= status <= 299:
                        print('\t\t\t[-] ERROR: {}, HTTP {} : {}'.format(filename, status, text))

class GithubApi(HttpApi):

    apiUrl = 'https://api.github.com'
    uploadUrl = 'https://uploads.github.com'
    genericHeaders = { 'Accept' : 'application/vnd.github.v3+json' }

    def __init__(self, owner, repo, token):
        self.owner = owner
        self.repo = repo

        self.genericHeaders['Authorization'] = 'token ' + token

    def getReleases(self):
        url = self.apiUrl + '/repos/{}/{}/releases'.format(self.owner, self.repo)

        status, text = self.get(url, self.genericHeaders)

        return json.loads(text) if self.isStatusValid(status) else None

    def getRelease(self, tag):
        releases = self.getReleases()

        for release in releases:
            if release['tag_name'] == tag:
                return release

        return None
    
    def createRelease(self, tag_name, target_commitish, name, body, draft=False, prerelease=False):
        url = self.apiUrl + '/repos/{}/{}/releases'.format(self.owner, self.repo)

        data = {
            'tag_name' : tag_name,
            'target_commitish' : target_commitish,
            'name' : name,
            'body' : body,
            'draft' : draft,
            'prerelease' : prerelease
        }

        status, text = self.post(url, headers=self.genericHeaders, data=data)

        if not self.isStatusValid(status):
            raise Exception('Could not create release:', status, text)

        return json.loads(text)

    def uploadReleaseAsset(self, release, filename):
        url = self.uploadUrl + '/repos/{}/{}/releases/{}/assets?name={}'.format(self.owner, self.repo, release['id'], filename)
        headers = { 'Content-Type' : 'application/zip' }
        headers.update(self.genericHeaders)

        file = { 'file' : (filename, open(prefixPath + '/' + filename, 'rb'))}
        
        status, text = self.post(url, headers, None, file)

        return json.loads(text) if self.isStatusValid(status) else None
    
    def uploadReleaseAssets(self, release, files):
        for file in files:
            self.uploadReleaseAsset(release, file)

def getReleaseMessage(changelog, tag):

    s = """

Each `yall` release is available from `.deb` and `.rpm` repositories :
* `.deb` : `curl -s https://packagecloud.io/install/repositories/naccyde/yall/script.deb.sh | sudo bash`
* `.rpm` : `curl -s https://packagecloud.io/install/repositories/naccyde/yall/script.rpm.sh | sudo bash`

You can then install `yall` and `yall-dev` using your package manager. The following distributions are supported :
* Debian : `wheezy (7)`, `jessie (8)`, `stretch (9)`, `buster (10)`
* Ubuntu : `Trusty Tarh (14.04)`, `Xenial Xerus (16.04)`, `Artful Ardvark (17.10)`, `Bionic Beaver (18.04)`
* Fedora : `25`, `26`, `27`

If your distribution is not supported, you can open an issue to ask to its support.
"""

    return changelog + s

def main():
    parser = argparse.ArgumentParser(description='Script used to deploy yall releases')
    parser.add_argument('-g', '--github-token', required=True, help='Github token')
    parser.add_argument('-p', '--package-cloud-token', required=True, help='Package Cloud token')
    parser.add_argument('-t', '--tag', required=True, help='Tag of the release')
    parser.add_argument('-z', '--zip', action='store_true', help='Deploy .zip artefacts')
    parser.add_argument('-l', '--linux', action='store_true', help='Deploy .deb and .rpm artefacts')
    args = parser.parse_args()

    lastChangelog = ""
    with open("CHANGELOG.md", "r") as file:
        lastChangelogWVersion = file.read().split("\n\n")[2]
        lastChangelog = '\n'.join(lastChangelogWVersion.split("\n")[1:])

    print('=== yall release ===\n')
    print('\t[+] Creating release {}\n'.format(args.tag))
    
    # Create Github release
    githubApi = GithubApi(owner, repo, args.github_token)
    release = githubApi.getRelease(args.tag)
    if not release:
        print('\t[+] Creating release', args.tag)
        release = githubApi.createRelease(args.tag, 'master', args.tag, getReleaseMessage(lastChangelog, args.tag))
    else:
        print('\t[.] Release', args.tag, 'already exists')

    if args.zip:
        print('\t[+] Deploying .zip artefacts')
        zipArtefacts = getArtefacts(prefixPath, '*.zip')
        githubApi.uploadReleaseAssets(release, zipArtefacts)

    if args.linux:
        print('\t[+] Deploying .deb and .rpm artefacts')
        packageCloudApi = PackageCloudApi(owner, 'yall', args.package_cloud_token)

        distrosPackages = findDistroIds(requiredDistros, packageCloudApi.getDistributions()[1])
        distrosPackages['deb']['filename'] = getArtefacts(prefixPath, '*.deb')
        distrosPackages['rpm']['filename'] = getArtefacts(prefixPath, '*.rpm')
        packageCloudApi.uploadPackages(distrosPackages)

    print('\t[+] RELEASED !')

if __name__== "__main__":
    main()

