#!/bin/bash
echo "invalid command || ifconfig; echo hello world!!!!; git --help; ls -a; git status;" | bin/rshell
echo "ls -a && ifconfig; invalid command || git --help; ls -a || ls && exit;" | bin/rshell
echo "ls || invalid command" | bin/rshell
echo "echo the quick brown fox... && echo jumped over the lazy dog" | bin/rshell
echo "git status && echo Test Successful" | bin/rshell
