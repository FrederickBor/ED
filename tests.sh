#!/bin/bash

for i in `ls -d */` ; do
    FOLDER_DIR="$PWD"

    if [ -f "${FOLDER_DIR}/$i/compileAndRun.sh" ]; then
        cd "${FOLDER_DIR}/$i"
        source "${FOLDER_DIR}/$i/compileAndRun.sh"
        cd ..
    fi
done