#!/bin/sh

set -e

clang -Wall -Wextra -Weverything test.c -o test -lmtrie

# Test 1: insert & search
./test -i caravan -s caravan | tail -n 1 | grep -q "Found"
./test -i caravan -s carpool | tail -n 1 | grep -q "Not found"

# Test 2: node count
./test -i caravan -i carpool -n | tail -n 1 | grep -q "12" 
./test -i boat    -i goat    -n | tail -n 1 | grep -q "9"

# Test 3: remove & trim
./test -i caravan -r caravan    -n | tail -n 1 | grep -q "8"
./test -i caravan -r caravan -t -n | tail -n 1 | grep -q "1"
