#!bin/bash
echo "touch stuff.txt; ls -a > stuff.txt; cat stuff.txt; rm stuff.txt" | bin/rshell
echo "touch ender.txt; ls -a && ifconfig > ender.txt; cat ender.txt; rm ender.txt" | bin/rshell
echo "touch helloworld.txt; git status > helloworld.txt; git >> helloworld.txt; cat helloworld.txt; rm helloworld.txt" | bin/rshell
echo "touch foo.txt; echo foo.txt > "this is a file"; echo foo.txt >> "Appending to the file."; cat foo.txt; rm foo.txt" | bin/rshell
echo "touch fooo.txt; ls src > fooo.txt; cat fooo.txt; rm fooo.txt" | bin/rshell
