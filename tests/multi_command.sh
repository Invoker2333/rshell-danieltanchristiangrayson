#!/bin/bash
echo "invalid command || ifconfig; echo hello world!!!!; git --help; ls -a; git status;" | ./a.out
echo "ls -a && ifconfig; invalid command || git --help; ls -a || ls && exit;" | ./a.out
echo "ls || invalid command" | ./a.out
echo "echo the quick brown fox... && echo jumped over the lazy dog" | ./a.out
echo "git status && echo Test Successful" | ./a.out
