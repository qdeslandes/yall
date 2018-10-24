#!/bin/bash

# Script used to fully build the software

set -ex

YALL_ROOT=`pwd`
BRANCH=`git rev-parse --abbrev-ref HEAD`
GITHUB_REPO=naccyde/yall
MAJOR=$(echo $TRAVIS_TAG | cut -d. -f1)
MINOR=$(echo $TRAVIS_TAG | cut -d. -f2)
PATCH=$(echo $TRAVIS_TAG | cut -d. -f3)

# Create build and output directories
rm -rf ${YALL_ROOT}/build || true

# Debug build
cmake -B${YALL_ROOT}/build -H${YALL_ROOT} -DCMAKE_BUILD_TYPE=Debug -DYALL_VERSION_MAJOR=${MAJOR} -DYALL_VERSION_MINOR=${MINOR} -DYALL_VERSION_PATCH=${PATCH}
make -C ${YALL_ROOT}/build -j 9 package

# Release build
cmake -B${YALL_ROOT}/build -H${YALL_ROOT} -DCMAKE_BUILD_TYPE=Release -DYALL_VERSION_MAJOR=${MAJOR} -DYALL_VERSION_MINOR=${MINOR} -DYALL_VERSION_PATCH=${PATCH}
build-wrapper-linux-x86-64 --out-dir ${YALL_ROOT}/build/out/bw make -C ${YALL_ROOT}/build -j 9 package

make -C ${YALL_ROOT}/build test
make -C ${YALL_ROOT}/build doc

if [ "$TRAVIS_PULL_REQUEST" = "false" ] && [ "$BRANCH" = "develop" ]; then
    SONAR_EXTRA_OPTIONS="-Dsonar.branch.target=develop -Dsonar.branch.name=${BRANCH}"
else
    SONAR_EXTRA_OPTIONS="-Dsonar.pullrequest.branch=${BRANCH} -Dsonar.pullrequest.key=${TRAVIS_PULL_REQUEST} -Dsonar.pullrequest.base=develop -Dsonar.pullrequest.provider=github -Dsonar.pullrequest.github.repository=${GITHUB_REPO}"
fi

sonar-scanner \
    -Dproject.settings=${YALL_ROOT}/.sonar-project.properties \
    -Dsonar.host.url=https://sonarcloud.io \
    -Dsonar.cfamily.build-wrapper-output=${YALL_ROOT}/build/out/bw \
    -Dsonar.projectBaseDir=${YALL_ROOT} \
    -Dsonar.cfamily.gcov.reportsPath=${YALL_ROOT}/build/out/coverage \
    -Dsonar.login=${SONAR_API_KEY} \
    -Dsonar.projectVersion=${TRAVIS_TAG} ${SONAR_EXTRA_OPTIONS}
