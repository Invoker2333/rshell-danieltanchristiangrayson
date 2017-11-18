#!/bin/bash
echo "exit" | bin/rshell
echo "ls -a; git status; ifconfig; git; exit" | bin/rshell
echo "git && ls -a; ifconfig || echo Hello Everybody!!!; exit" | bin/rshell
echo "ls && echo "Hello World!!!" && git status;" | bin/rshell
echo "(echo "Hello World" && nonCommand) || (exit && echo A)" | bin/rshell