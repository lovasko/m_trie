#!/bin/bash

function run_test {
  printf "Running test #${1} ... "
  RESULT=$(./test $2)
  if echo "$RESULT" | tail -n 1 | grep -q "$3"
  then
    printf "\e[32mOK\e[0m\n"
  else
    printf "\e[31mFAIL\e[0m\nFull output of test #${1}:\n${RESULT}\n"
  fi
}

clang -Wall -Wextra -Weverything test.c -o test -lmtrie

run_test 01 '-i caravan -s caravan'                           Found
run_test 02 '-i caravan -s carpool'                           'Not found'
run_test 03 '-i caravan -i carpool -n'                        12
run_test 04 '-i boat    -i goat -n'                           9
run_test 04 '-i taob    -i taog -n'                           6
run_test 05 '-i caravan -r caravan -n'                        8
run_test 06 '-i caravan -r caravan -t -n'                     1
run_test 07 '-i carpool -i caravan -i boat -p car -s caravan' 'Not found'
run_test 08 '-i carpool -i caravan -i boat -p car -s boat'    Found
run_test 09 '-i abc -i def -i ghi -i jkl -i mno -a -t -n'     1
run_test 10 '-r nonexistent -n'                               1
run_test 11 '-a -n'                                           1
run_test 12 '-a -l'                                           0
run_test 13 '-i zzz -i aaa -r aaa -t -n -r zzz -t -n'         1
run_test 14 '-i caravan -l'                                   7
run_test 15 '-i caravan -i car -r caravan -l'                 7
run_test 16 '-i caravan -i car -r caravan -t -l'              3
run_test 17 '-i caravan -i car -r caravan -t -n'              4
run_test 18 '-i caravan -i cartoonish -r caravan -t -l'       10
run_test 19 '-i caravan -i cartoonish -r cartoonish -t -l'    7
run_test 20 '-i boat -a -i boat -s boat'                      Found
run_test 21 '-i boat -a -t -i boat -s boat'                   Found
run_test 22 '-i a -i b -i c -a -t -n'                         1
run_test 23 '-i caravan -i carpool -p car -t -n'              1
run_test 24 '-i caravan -i carpool -i ca -p car -t -n'        3
