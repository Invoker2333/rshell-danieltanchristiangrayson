#!/bin/bash
echo "ls -a; ifconfig; #git status;" | bin/rshell
echo "ls -a; #ifconfig; git status;" | bin/rshell
echo "ifconfig; #git status;" | bin/rshell
echo "#alsdkjflaksdjflaskdjflaksdj" | bin/rshell
echo "echo Hello World!!!!! #git; git; git; git status" | bin/rshell
echo "ls #-a comment" | bin/rshell
echo "(echo A && echo B) && echo C #&& (echo D && echo E)" | bin/rshell

