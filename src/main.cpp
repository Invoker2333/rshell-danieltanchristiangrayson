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
//#include <sys/wait.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int executeCommands(char ** argv);
void recursion(int prev, char **parsedTokens, char *statements);
void handleCommands(char *commands);
void changeBuffer(std::basic_string<char> &buffer);
int validBrackets(const char *const string);
int checkForFile(const char *const fileName, const char *const flags = "-e");
void handleCommandsWithBrackets(int &num, char *commands);

int main() {
	std::basic_string<char> buffer;
	while(1) {
		printf("$: ");
		std::getline(std::cin, buffer);
		if(std::cin.fail() || buffer == "exit") {
			printf("End of program.\n");
			return 0;
		}

		changeBuffer(buffer);

		char *temp = (char *)buffer.c_str();

		handleCommands(temp);
		buffer.clear();
	}
}

int validBracketsRecursion(int &i, const char *const str) {
	while(1)
		switch(str[i]) {

		case '\0':
			return '\1';

		case '[':{
			for(i++; str[i] != ']'; i++) {
				if(str[i] == '[' || str[i] == '(' || str[i] == ')' || str[i] == '\0') return 0;
			} i++;
			break;
		}

		case '(':
			i++;
			if(validBracketsRecursion(i, str) != ')') return 0;
			break;

		case ')':
			i++;
			return ')';

		case ']':
			return 0;

		default:
			i++;

		}//switch
}

int validBrackets(const char *const str) {
	int i = 0; int ret = validBracketsRecursion(i, str);
	return ret && ret != int(')');
}

void changeBuffer(std::basic_string<char> &buffer) {
	//brute force...a bit ugly... TO DO: perhaps a better way to do this?!?!?
	buffer = "  " + buffer;

	for(std::size_t i = 2; i < buffer.length(); i++) {
		if(buffer[i] == '#') {
			buffer = buffer.substr(0, i);//cut off anything after '#'
			return;
		} else if(buffer[i] == '&' && buffer[i - 1] == '&' && buffer[i - 2] != ' ') {
			buffer = buffer.substr(0, i - 1) + " && " + buffer.substr(i + 1);
			i+=2;
		} else if(buffer[i] == '|' && buffer[i - 1] == '|' && buffer[i - 2] != ' ') {
			buffer = buffer.substr(0, i - 1) + " || " + buffer.substr(i + 1);
			i+=2;
		} else if(buffer[i] == '(' && (buffer[i - 1] != ' ' || buffer[i + 1] != ' ')) {
			buffer = buffer.substr(0, i) + " ( " + buffer.substr(i + 1);
			i+=2;
		} else if(buffer[i] == ')' && buffer[i - 1] != ' ') {
			buffer = buffer.substr(0, i) + " ) " + buffer.substr(i + 1);
			i+=2;
		}  else if(buffer[i] == '[' && buffer[i - 1] != ' ') {
			buffer = buffer.substr(0, i) + " [ " + buffer.substr(i + 1);
			i+=2;
		} else if(buffer[i] == ']' && buffer[i - 1] != ' ') {
			buffer = buffer.substr(0, i) + " ] " + buffer.substr(i + 1);
			i+=2;
		}
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
		if(validBrackets(statements[i])) {
			printf("Statement #: %d\n",i);
			int k = 0;
			for(char *tok = strtok(statements[i], " "); tok; tok = strtok(0, " ")) {
				parsedTokens[k] = tok;
				printf("Token #%d: %s\n", k, parsedTokens[k]);
				k++;
			}

			//recursion(1, parsedTokens, strtok(statements[i], " "));
			for(int j = 0; parsedTokens[j]; j++) parsedTokens[j] = 0;//Cleanup: just in case...
		} else {
			printf("Invalid parenthesis/brackets\n");
		}
	}
}

void recursion(int prev, char **parsedTokens, char *statements) {
	if(statements == 0 || *statements == '#') {
		return;
	} else if(strcmp(statements, "&&") == 0) {
		if(prev) recursion(1, parsedTokens, strtok(0, " "));
		else {
			char *next = strtok(0, " ");
			while(next && *next != '#' && strcmp(next, "&&") && strcmp(next, "||")) {
				next = strtok(0, " ");
			}
			printf("recursion &&: %d\n", prev);
			recursion(prev, parsedTokens, strtok(0, " "));
		}
	} else if(strcmp(statements, "||") == 0) {
		if(!prev) recursion(1, parsedTokens, strtok(0, " "));
		else {
			char *next = strtok(0, " ");
			while(next && *next != '#' && strcmp(next, "&&") && strcmp(next, "||")) {
				next = strtok(0, " ");
			}
			printf("recursion ||: %d\n", prev);
			recursion(prev, parsedTokens, strtok(0, " "));
		}
	} else {
		int i; char *next = strtok(0, " "); *parsedTokens = statements;
		for(i = 1; next && *next != '#' && strcmp(next, "&&") && strcmp(next, "||"); i++) {
			parsedTokens[i] = next;
			next = strtok(0, " ");
		}

		recursion(executeCommands(parsedTokens), parsedTokens + i + 1, next);
	}
}

int executeCommands(char ** argv) {
	//pid_t pid;
	//int status;

	//test -e test/file/path && echo “path exists”
	//					- or -
	//$ [ -e test/file/path ] && echo “path exists”
	printf("%s\n", *argv);

	if(argv[0][0] == '[' || strcmp(*argv, "test") == 0) {
		if(argv[1] == 0 || argv[1][0] == ']')
			return 0;
		else if(argv[2] == 0)
			return checkForFile(argv[1]);
		else if(argv[1][0] == '-' && isalpha(argv[1][1])) {
			return checkForFile(argv[2], argv[1]);//[ -e test/file/path ]
		} else {
			return checkForFile(argv[1]);//[ test/file/path ]????
		}
	}
	/*
	if((pid = fork()) < 0) {
		perror("forking child process failed\n");
		return 0;
	}
	if(pid == 0) {
		if(execvp(*argv, argv) < 0) {
			perror("exec failed\n");
			return 0;
		}
	}
	while(wait(&status) != pid)
		;*/
	return 0;
}

void handleCommandsWithBrackets(int &num, char *str) {
	//std::vector<char *> array;

	while(1)
		switch(str[num]) {

		case '\0':
			return;

		case '[':
			num++;
			handleCommandsWithBrackets(num, str);
			//if(brackets(num, str) != ']') return '\0';
			break;

		case '(':
			num++;
			handleCommandsWithBrackets(num, str);
			//if(brackets(num, str) != ')') return '\0';
			break;

		case ')':
			str[num] = '\0';
			num++;
			return;// ')';

		case ']':
			str[num] = '\0';
			num++;
			return;// ']';

		default:
			num++;

		}//switch
}

int checkForFile(const char *const fileName, const char *const flags) {
	// -e => checks if file directory exists
	// -f => checks if file directory exists & is regular
	// -d => checks if file directory exists & is directory
	struct stat sb;
	if (stat(fileName, &sb) != 0) {
		printf("file does not exist\n");
		return 0;
	} else if(strcmp(flags, "-f")) {
		if((sb.st_mode & S_IFMT) == S_IFREG) {
			printf("file exists and is regular\n");
			return 1;
		} else {
			printf("file is not regular\n");
			return 0;
		}
	} else if(strcmp(flags, "-d")) {
		if((sb.st_mode & S_IFMT) == S_IFDIR) {
			printf("file exists and is a directory\n");
			return 1;
		} else {
			printf("file is not a directory\n");
			return 0;
		}
	} else {
		printf("file exists\n");
		return 1;
	}
}
