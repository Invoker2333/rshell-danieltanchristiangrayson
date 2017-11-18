#!/bin/sh
echo "test -e src/main.cpp" | bin/rshell
echo "test -f src/main.cpp" | bin/rshell
echo "test -d src/main.cpp" | bin/rshell
echo "[ -e tests/test_test.sh ]" | bin/rshell
echo "[ -f tests/test_test.sh ]" | bin/rshell
echo "[ -d tests/test_test.sh ]" | bin/rshell
echo "test -e tests && echo Path Exists" | bin/rshell
echo "test -f tests && echo Path Exists and is a regular file" | bin/rshell
echo "test -d tests && echo Path Exists and is a directory" | bin/rshell 
echo "(echo A || echo B) && (test -d tests && echo Path Exists and is a directory)" | bin/rshell