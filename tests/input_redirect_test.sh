#!/bin/bash
echo "cat < src/main.cpp" | bin/rshell
echo "touch foo.txt; echo "Hello World!!!" > foo.txt; cat < foo.txt; rm foo.txt" | bin/rshell
echo "echo < src" | bin/rshell

