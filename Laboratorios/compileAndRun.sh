#!/bin/bash

FOLDER_DIR="$PWD"

for i in `ls "${FOLDER_DIR}"` ; do
    if [ -d "${FOLDER_DIR}/$i" ]; then
        if [ -f "${FOLDER_DIR}/$i/test.sh" ]; then
            cd "${FOLDER_DIR}/$i"
            source "${FOLDER_DIR}/$i/test.sh"
            cd ..
        fi
    fi
done