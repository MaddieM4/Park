#!/bin/sh

## Park is open source software.
## It's a frontend for a package manager, and checkinstall, and gorepo.

VERSION="Park v0.01"

E_WRONGARGS=85

error() {
	echo "$2" >&2;
	exit $1;
}

haveprog() {
	[ -x "$(which $1)" ]
}

# Aptitude uses apt-get for backend, use aptitude if both are installed
if haveprog aptitude ; then MANAGER="aptitude"
elif haveprog apt-get ; then MANAGER="apt-get"
elif haveprog up2date ; then MANAGER="up2date"
elif haveprog yum ; then MANAGER="yum"
else
	error 127 "Could not find a package manager to use as backend"
fi

do_plus() {
	if [ -z "$1" ]
	then
		# List manual installations
		echo "Manually installed packages:"
		echo
		case "$MANAGER" in
		"aptitude"	) aptitude -F "%p" search \!~M~i~T
		esac
	else
		# Install packages
		# TODO: repos
		case "$MANAGER" in
		"aptitude"	) aptitude install "$@";;
		"apt-get"	) apt-get install "$@";;
		esac
	fi;
	exit 0
}

do_minus() {
	if [ -z "$1" ]
	then
		# Autoremove
		case "$MANAGER" in
		"apt*"	) apt-get autoremove;;
		esac
	else
		# Uninstall packages
		case "$MANAGER" in
		"apt*"	) apt-get remove "$@";;
		esac
	fi;
	exit 0
}

do_search() {
	case "$MANAGER" in
	"aptitude"	) aptitude search "$@";;
	"apt-get"	) apt-get search "$@";;
	esac
}

case "$1" in
"+"	) shift; do_plus "$@";;
"-"	) shift; do_minus "$@";;
"x"	) shift; do_plus "$@";;
"/"	) shift; do_plus "$@";;
"."	) shift; do_plus "$@";;
"?"	) shift; do_search "$@";;
"--manager"	) echo $MANAGER;;
"--version"	) echo $VERSION;;
*	) error $E_WRONGARGS "Bad first argument, expected + - x / or . and got $1";;
esac
