#!/bin/sh

# Script used to create a new yall release
# Required variables (from environment)
#  - YALL_VERSION

set -xe

# Check mandatory variables
: "${YALL_VERSION?ERROR: Must set YALL_VERSION}"

echo "INFO: Creating release $YALL_VERSION"

git fetch --all --prune --tags

# Does tag exists ?
if git rev-parse ${YALL_VERSION} >/dev/null 2>&1
then
    echo "ERROR: Tag already exists"
    exit 1
fi

# Check if the directory is clean
if [ "$(git status --porcelain)" ]
then
    echo "ERROR: Directory contains uncommitted changes"
    exit 1
fi

# Check if the directory is clean
if [ "$(git cherry -v)" ]
then
    echo "ERROR: Directory contains unpushed commits"
    exit 1
fi

# Change version number
git checkout develop
sed -i "s/Unreleased/$YALL_VERSION/g" CHANGELOG.md
sed -i '6i## [Unreleased]\n### Added\n### Changed\n### Deprecated\n### Removed\n### Fixed\n### Security\n' CHANGELOG.md
git commit -a -m"Update version to $YALL_VERSION"
git pull
git push

# Merging
git checkout master
git pull
git merge --squash develop
git commit -a -m"Merge branch 'develop' for version ${YALL_VERSION}"

git tag ${YALL_VERSION} master

git push
git push --tags

# Merge release commit on develop
git checkout develop
git merge master -m"Release ${YALL_VERSION}"
git push

echo "INFO: Released !"