#!/bin/bash

SCRIPT=${BASH_SOURCE[0]}
SCRIPTPATH=$(realpath $(dirname $SCRIPT))
PROJECT_DIR=code
PROG1_DIR=${PROJECT_DIR}/prog1
PROG2_DIR=${PROJECT_DIR}/prog2
REPORT_FILE=rapport.pdf
ARCHIVE=rendu.tar.gz

cd $SCRIPTPATH

if [ ! -f "$REPORT_FILE" ]
then
    echo "Could not find $REPORT_FILE directory in $SCRIPTPATH" >&2
    exit 1
fi

echo "The following files are archived in $ARCHIVE : "
tar --exclude="$ARCHIVE" --exclude='*.o' --exclude='*.user' -czvf $ARCHIVE ${PROJECT_DIR}/${PROJECT_FILE} $PROG1_DIR $PROG2_DIR $REPORT_FILE
