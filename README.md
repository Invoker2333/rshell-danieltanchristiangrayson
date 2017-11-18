Authors: Christian Grayson, Daniel Tan
Contact Info: cgray009@ucr.edu, dtan004@ucr.edu

Overview:
This program allows users to type in Linux shell script commands. You can chain together
multiple commands through the '&&', '||', and ';'. Anything after the '#' is treated
as a comment and therefore not executed. Typing in "test -e test/file/path" or "[-e test/file/path]"
can be used to check if a directory exists or not, determine whether it is a regular file, and/or
determine whether it is a directory. If there is no flag, -e functionality is used by default. Parentheses
operators can be used to change the order in which commands are executed. Mutliple parentheses/nested
parentheses can be used to fine-tune the order of execution. If there is an uneven amount of parentheses,
the program can effectively errors in parentheses.

Files:
-Readme.md
-tests subdirectory containing shell script tests to unit test/stress test
the program, the tests are written in shell script
-src subdirectory contains all the header(.h) and source files(.cpp)

Terms of Use:

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

This project allows users to take in command-line arguments and executes the command line arguments.
The "cd" commands is currently not supported. Users can chain together combinations of '&&', '||' 
and ';' to execute complex shell script commands.

Bug Report:

-recursion bug where it would end up in an infinite loop (fixed)
-shell scripting bug where it would continuously call an infinite loop (fixed)
-shell script tests fail to call the program correctly (fixed)
-precendence bugs
-shell script tests have problems (hopefully caught most of them.)

