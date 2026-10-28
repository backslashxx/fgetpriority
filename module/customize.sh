#!/bin/sh
PATH=/data/adb/ksu/bin:$PATH
export MODULE_HOT_INSTALL_REQUEST="true"

chmod +x $MODPATH/binary

if ! $MODPATH/binary reset > /dev/null 2>&1; then
	abort "[!] not supported"
fi

$MODPATH/binary setall 2>/dev/null

# EOF
