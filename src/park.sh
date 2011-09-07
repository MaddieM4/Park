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
elif haveprog installpkg ; then MANAGER="slack" # Slackware can do slack/rpm
elif haveprog rpm ; then MANAGER="rpm"
else
	error 127 "Could not find a package manager to use as backend"
fi

packages() {
	# Argument 1:: space type
	# Argument 2:: search term
	case "$MANAGER" in
	apt*	) case $1 in
		  space ) ALL=`dpkg-query -W -f='${Package} '`;;
		  * ) ALL=`dpkg-query -W -f='${Package}\n'`;;
		  esac;;
	esac
	if [ -z "$2" ]
	then
		PACKAGES=$ALL
	else
		STERM=`echo "$2" | sed 's/*/.*/g'`
		PACKAGES=`echo "$ALL" | grep -x "$STERM"`
	fi
}

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
}

do_minus() {
	if [ -z "$1" ]
	then
		# Autoremove
		case "$MANAGER" in
		apt*	) apt-get autoremove;;
		esac
	else
		# Uninstall packages
		case "$MANAGER" in
		apt*	) apt-get remove "$@";;
		esac
	fi;
}

update() {
	# Total update
	echo "Updating metadata"
	case "$MANAGER" in
	"aptitude"	) aptitude update;;
	"apt-get"	) apt-get update;;
	esac
}

upgrade() {
	# Upgrade
	if [ "$1" = '*' ]
	then
		upgradeall
	else
		packages space $1
		case "$MANAGER" in
		apt*	) apt-get install $PACKAGES;;
		esac
	fi
}

upgradeall() {
	case "$MANAGER" in
	apt*	) apt-get upgrade;;
	esac
}

do_x() {
	if [ -z "$1" ]
	then
		update
	else
		upgrade "$1"
	fi;
}

do_div() {
	if [ -z "$1" ]
	then
		# List all packages
		packages
		echo "$PACKAGES"
	else
		# Package metadata
		case $MANAGER in
		aptitude	) aptitude show "$@";;
		apt-get	) apt-cache show "$@";;
		esac
	fi;
}

do_search() {
	packages nl "$@"
	echo "$PACKAGES"
}

do_global_search() {
	case "$MANAGER" in
	"aptitude"	) aptitude search "$@";;
	"apt-get"	) apt-get search "$@";;
	esac
}

case "$1" in
"+"	) shift; do_plus "$@";;
"-"	) shift; do_minus "$@";;
"x"	) shift; do_x "$@";;
"xx"	) shift; upgradeall;;
"xxx"	) shift; update; upgradeall;;
"/"	) shift; do_div "$@";;
"."	) shift; do_plus "$@";;
"?"	) shift; do_search "$@";;
"??"	) shift; do_global_search "$@";;
"--manager"	) echo $MANAGER;;
"--version"	) echo $VERSION;;
*	) error $E_WRONGARGS "Bad first argument, expected + - x / . or ? and got $1";;
esac
