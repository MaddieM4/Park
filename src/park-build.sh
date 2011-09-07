#!/bin/sh

if [ -z "$1" ] then
	DIR = `pwd`
else
	DIR =" $1"
fi

MANAGER=`park --manager`

case $MANAGER in
apt*	) PARK_PKGTYPE=D
slack	) PARK_PKGTYPE=S
rpm	) PARK_PKGTYPE=R

park-meta $PARK_PKGTYPE -e "$DIR"

checkinstall --pakdir "/usr/src/pkg/" -$PARK_PKGTYPE $PARK_CI_COMMAND >&2

echo "/usr/src/pkg/"
