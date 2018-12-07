#!/bin/sh

set -ex

: "${TRAVIS_PULL_REQUEST?ERROR: You must set TRAVIS_PULL_REQUEST}"
: "${TRAVIS_TAG?ERROR: You must set TRAVIS_TAG}"
: "${TRAVIS_BRANCH?ERROR: You must set TRAVIS_BRANCH}"
: "${TRAVIS_COMMIT?ERROR: You must set TRAVIS_COMMIT}"
: "${SONAR_TOKEN?ERROR: You must set SONAR_TOKEN}"

docker run -u `id -u $USER` -e TRAVIS_PULL_REQUEST=${TRAVIS_PULL_REQUEST} -e TRAVIS_TAG=${TRAVIS_TAG} -e TRAVIS_BRANCH=${TRAVIS_BRANCH} -e TRAVIS_COMMIT=${TRAVIS_COMMIT} -e SONAR_TOKEN=${SONAR_TOKEN} --rm -v `pwd`:/code naccyde/yall /code/resources/build.sh

docker run --rm -v `pwd`/build/out/packages:/packages debian:buster-slim /bin/bash -c "apt update && apt install -y libjansson-dev && dpkg -I /packages/yall_*.deb && dpkg -i /packages/yall_*.deb && dpkg -I /packages/yall-dev_*.deb && dpkg -i /packages/yall-dev_*.deb"

docker run --rm -v `pwd`/build/out/packages:/packages:delegated fedora:28 /bin/bash -c "dnf install -y jansson-devel && rpm -qip /packages/yall-[0-9]* && rpm -i /packages/yall-[0-9]* && rpm -qip /packages/yall-devel-[0-9]* && rpm -i /packages/yall-devel-[0-9]*"
