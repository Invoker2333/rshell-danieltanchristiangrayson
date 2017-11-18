#!/bin/bash
echo "echo A && echo B || echo C && echo D" | bin/rshell
echo "(echo A && echo B) || (echo C && echo D)" | bin/rshell
echo "(e A && echo B) || (echo C && echo D)" | bin/rshell
echo "(ls && fail) || echo A" | bin/rshell
