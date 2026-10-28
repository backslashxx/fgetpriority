#!/bin/sh
PATH=/data/adb/ksu/bin:$PATH
MODDIR="/data/adb/modules/fgetpriority"

$MODDIR/binary setall > /dev/null 2>&1

# EOF
