#!/bin/bash

echo "Executing Examen 2"

g++ main.cpp -o a.out &&
./a.out < input.in > output.txt && 
diff -u output.txt expectedOutput.txt

status=$?

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m'

[ $status -eq 0 ] && echo -e "${GREEN}OK!${NC}" || echo -e "${RED}FAILED!${NC}"