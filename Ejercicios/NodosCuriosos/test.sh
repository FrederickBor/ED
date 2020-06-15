#!/bin/bash

echo "Executing Nodos Curiosos"

g++ main.cpp -o a.out &&
./a.out < input.in > output.txt && 
diff -u output.txt expectedOutput.txt

status=$?

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m'

[ $status -eq 0 ] && echo -e "${GREEN}OK!${NC}" && exit 0 || echo -e "${RED}FAILED!${NC}" && exit -1