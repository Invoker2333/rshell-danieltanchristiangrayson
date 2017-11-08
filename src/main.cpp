/*
Copyright 2017, 2018 Christian Grayson & Daniel Tan

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
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstdlib>
//////
// return 1 if successful, return 0 if NOT successful
int executeCommands(char ** argv) {
	pid_t pid;
	int status;

	if((pid = fork()) < 0) {
		perror("forking child process failed\n");
		return 0;
	}
	else if(pid == 0) {
		if(execvp(*argv, argv) < 0) {
			perror("exec failed\n");
			return 0;
		}
	}
	while(wait(&status) != pid)
		;
	return 1;
}

void recursion(int prev, char **parsedTokens, char *statements) {
	if(statements == 0 || *statements == '#') {
		return;
	} else if(strcmp(statements, "&&") == 0) {
		if(prev)	recursion(1, parsedTokens, strtok(0, " "));
	} else if(strcmp(statements, "||") == 0) {
		if(!prev) recursion(1, parsedTokens, strtok(0, " "));
	} else {
		int i; char *next = strtok(0, " "); *parsedTokens = statements;
		for(i = 1; next && *next != '#' && strcmp(next, "&&") && strcmp(next, "||"); i++) {
			parsedTokens[i] = next;
			next = strtok(0, " ");
		}

		recursion(executeCommands(parsedTokens), parsedTokens + i + 1, next);
	}
}

void handleCommands(char *commands) {
	char *statements[1024] = {0};
	char *parsedTokens[1024] = {0};
	int i = 0;

	for(char *tok = strtok(commands, ";"); tok; tok = strtok(0, ";")) {
		statements[i] = tok;
		i++;
	}

	for(int i = 0; statements[i]; i++) {
		recursion(1, parsedTokens, strtok(statements[i], " "));
		
		//Cleanup: just in case...
		for(int j = 0; parsedTokens[j]; j++) {
			parsedTokens[j] = 0;
		}
	}
}

void changeBuffer(std::basic_string<char> &buffer) {
	for(std::size_t i = 2; i < buffer.length(); i++) {
		if(buffer[i] == '&' && buffer[i - 1] == '&' && buffer[i - 2] != ' ') {
			buffer = buffer.substr(0, i - 1) + " && " + buffer.substr(i + 1);
			i+=2;
		} else if(buffer[i] == '|' && buffer[i - 1] == '|' && buffer[i - 2] != ' ') {
			buffer = buffer.substr(0, i - 1) + " || " + buffer.substr(i + 1);
			i+=2;
		} else if(buffer[i] == '#' && buffer[i - 1] != ' ') {
			buffer = buffer.substr(0, i - 1) + + " #" + buffer.substr(i + 1);
			i+=2;
		}
		
	}
}

//function that returns 1 if true, 0 if false
int hasCorrectSyntax(char *buffer) {
	int brack = 0; int paren = 0;

	for(int i = 0; 1; i++) {
		switch(buffer[i]) {
			
		case '\0':
			return brack == 0 && paren == 0;

		case '[': 
			brack++;
			break;

		case ']':
			brack--;
			break;

		case '(':
			paren++;
			break;

		case ')':
			paren--;
			break;
		}
	}
}



int main() {
	std::basic_string<char> buffer;
	while(1) {
		printf("$: ");
		std::getline(std::cin, buffer);
		if(std::cin.fail()) {
			printf("End of program.\n");
			return 0;
		}

//		printf("%s\n", buffer.c_str());
//		changeBuffer(buffer);
		char *temp = (char *)buffer.c_str();
		if(hasCorrectSyntax(temp) == 1) printf("Correct!\n");
		else printf("Incorrect...\n");
//		if(strcmp(temp, "exit") == 0) {
//			printf("End of program.\n");
//			return 0;
//		} else if(buffer.empty())
//			continue;
		
//		handleCommands(temp);
		buffer.clear();
	}
}
