#!/bin/bash
echo "exit" | ./a.out
echo "ls -a; git status; ifconfig; git; exit" | ./a.out
echo "git && ls -a; ifconfig || echo Hello Everybody!!!; exit" | ./a.out
echo "ls && echo "Hello World!!!" && git status;" | ./a.out
