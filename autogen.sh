#!/bin/sh

ACLOCAL=aclocal
AUTOHEADER=autoheader
AUTOMAKE="automake -a -c --foreign"
AUTOCONF=autoconf
GNUM4=

echo -n "Locating GNU m4... "
for prog in $M4 gm4 gnum4 m4 ; do
  case `$prog --version 2>&1` in
    *GNU*) ok=yes
           GNUM4=$prog
	   echo "found: $GNUM4"
	   break ;;
    *) ;;
  esac
done
if test x$ok = xno ; then
    echo "not found."
fi

# Generate acinclude.m4
echo -n "Generate acinclude.m4... "
rm -f acinclude.m4
touch acinclude.m4
for fil in config/gettext.m4 config/lcmessage.m4 ; do
    cat $fil >> acinclude.m4
done
echo "done."

# Generate the Makefiles and configure files
if ( aclocal --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building macros... "
	$ACLOCAL
	echo "done."
else
	echo "aclocal not found -- aborting"
	exit
fi

if ( autoheader --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building config header template... "
	$AUTOHEADER
	echo "done."
else
	echo "autoheader not found -- aborting"
	exit
fi

if ( $AUTOMAKE --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building Makefile templates... "
	$AUTOMAKE
	echo "done."
else
	echo "automake not found -- aborting"
	exit
fi

if ( $AUTOCONF --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building configure... "
	$AUTOCONF
	echo "done."
else
	echo "autoconf not found -- aborting"
	exit
fi

echo -n "Creating POTFILES.in... "
cat <<EOF > tmppot
#
# This file is automatically generated by autogen.sh. This command was
# used to extract the files from the sources:
#
# grep -E "_\(\".*\"\)" \`find src -name \*.[hHC]\` | \\
# awk 'BEGIN {FS= ":"} {print $1}' | sort | uniq
#
# This must be done when standing in lyx/
#
# This is all the files that contains internationalization strings.

EOF

grep -l -E "_\(\".*\"\)" `find src -name \*.[hHC]` | \
awk 'BEGIN {FS= ":"} {print $1}' | sort -f -d | uniq >> tmppot
mv tmppot po/POTFILES.in
echo "done"

echo
echo 'run "./configure && make"'
echo
