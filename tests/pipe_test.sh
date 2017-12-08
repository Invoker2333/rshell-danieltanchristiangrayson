#!/bin/bash
echo "touch det.txt; echo "Hello World!!!" > det.txt; cat det.txt | sort; rm det.txt" | bin/rshell
echo "touch batty.txt; echo "Baseball" > batty.txt; cat < batty.txt | tr A-Z a-z > batty.txt; rm batty.txt" | bin/rshell
echo "ls -l | grep key | less" | bin/rshell
echo "ls -a | sort | git status" | bin/rshell
echo "touch infile && touch outfile; sort infile | uniq -C | sort -n > outfile; cat infile && cat outfile; rm infile && rm outfile" | bin/rshell
echo "touch xye; ls -lrt | tee xye; cat xye; rm xye" | bin/rshell