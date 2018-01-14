#!/bin/sh

REMOTE_VERSION=`git ls-remote --tags git@github.com:naccyde/yall.git | awk '{print $2}' | grep -v '{}' | awk -F"/" '{print $3}' | sort -V | tail -n 1`
CURRENT_VERSION=`cat $@/yall.version`

if [ "$REMOTE_VERSION" = "$CURRENT_VERSION" ]
then
	exit 1
else
	exit 0
fi
