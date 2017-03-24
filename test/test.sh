#!/bin/bash

function run_test {
  printf "Running test #${1} ... "
  RESULT=$(./test $2)
  if echo "$RESULT" | tail -n 1 | grep -q "$3"
  then
    printf "OK\n"
  else
    printf "FAIL\nFull output of test #${1}:\n${RESULT}\n"
  fi
}

clang -Wall -Wextra -Weverything test.c -o test -lmtrie
run_test 1 '-i caravan -s caravan'                           Found
run_test 2 '-i caravan -s carpool'                           'Not found'
run_test 3 '-i caravan -i carpool -n'                        12
run_test 4 '-i boat    -i goat -n'                           9
run_test 5 '-i caravan -r caravan -n'                        8 
run_test 6 '-i caravan -r caravan -t -n'                     1
run_test 7 '-i carpool -i caravan -i boat -p car -s caravan' 'Not found'
run_test 8 '-i carpool -i caravan -i boat -p car -s boat'    Found
run_test 9 '-i abc -i def -i ghi -i jkl -i mno -a -t -n'     1
