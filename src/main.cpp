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
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int validBracketsRecursion(int &i, char *const str, char **&brackets);
int validBrackets(char *const str, char **brackets);
void changeBuffer(std::basic_string<char> &buffer);
int handleTokens(char **tokenArray);
void handleEdgeCase(char *str);
int executeCommands(char ** argv);
int checkForFile(const char *const fileName, const char *const flags = "-e");
char *handleExpression(char *const str, char **&brackets);
int executeCommands(char ** argv);

int main(int , char *[]) {
	std::basic_string<char> buffer;
	char *statements[64] = {0};
	char *parsedParens[64] = {0};
	
	while(1) {
		printf("$: ");
		std::getline(std::cin, buffer);
		if(std::cin.fail() || buffer == "exit") {
			printf("End of program.\n");
			return 0;
		}

		changeBuffer(buffer);

		char *commands = (char *)malloc(sizeof(char) * (int)(buffer.length() + 1));
		strcpy(commands, buffer.c_str());
		
		int i = 0;
		for(char *tok = strtok(commands, ";"); tok; tok = strtok(0, ";")) {
			statements[i] = tok;
			i++;
		}
		
		for(int i = 0; statements[i]; i++) {
			if(validBrackets(statements[i], parsedParens)) {
				char **ptr = parsedParens;
				handleExpression(statements[i], ptr);
			} else {
				printf("Invalid parenthesis/brackets\n");
			}
		}
		
		for(int i = 0; statements[i]; i++)
			statements[i] = 0;//Cleanup
			
		for(int i = 0; parsedParens[i]; i++)
			parsedParens[i] = 0;//Cleanup
		
		free(commands);//Cleanup
		buffer.clear();
		
	}
}

int validBracketsRecursion(int &i, char *const str, char **&brackets) {
	while(1)
		switch(str[i]) {

		case '\0':
			return '\1';

		case '[':
			for(i++; str[i] != ']'; i++) {
				if(str[i] == '[' || str[i] == '(' || str[i] == ')' || str[i] == '\0') return 0;
			} i++;
			break;

		case '(':
			*brackets = str + i;
			brackets++;
			i++;
			if(validBracketsRecursion(i, str, brackets) != ')') return 0;
			break;

		case ')':
			*brackets = str + i;
			brackets++;
			i++;
			return ')';

		case ']':
			return 0;

		default:
			i++;

		}//switch
}

int validBrackets(char *const str, char **brackets) {
	int i = 0; int ret = validBracketsRecursion(i, str, brackets);
	return ret && ret != int(')');
}

void changeBuffer(std::basic_string<char> &buffer) {
	//brute force...a bit ugly... TO DO: perhaps a better way to do this?!?!?
	buffer = "  " + buffer;

	for(std::size_t i = 2; i < buffer.length(); i++) {
		if(buffer[i] == '#') {
			buffer = buffer.substr(2, i);//cut off anything after '#'
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
	
	buffer = buffer.substr(2);
}

int handleTokens(char **tokenArray) {	
	if(*tokenArray) {
		
		if(strcmp(*tokenArray, "&&") == 0) {
			*tokenArray = 0;
			int ret = handleTokens(tokenArray - 1);
			printf(" AND ");
			return ret;

		} else if(strcmp(*tokenArray, "||") == 0) {
			*tokenArray = 0;
			int ret = handleTokens(tokenArray - 1);
			printf(" OR ");
			return !ret;

		} else {

			while(*tokenArray && strcmp(*tokenArray, "&&") != 0 && strcmp(*tokenArray, "||") != 0)
				tokenArray--;
			int ret = handleTokens(tokenArray);
			//Off by one error...
			return ret? executeCommands(tokenArray + 1) : 0;

		}

	}
	
	return 1;
}

//handles a strange edge case....
void handleEdgeCase(char *str) {
	for(int i = 0; str[i]; i++) {
		if(str[i] == '(') {
			str[i] = '\0';
			char *tokens[32] = {0};
			int j = 0;
			for(char *tok = strtok(str, " "); tok; tok = strtok(0, " ")) {
				tokens[j] = tok;
			}
			printf("\nEDGE CASE: \n");
			for(j = 0; tokens[j]; j++) {
				printf("%s ", tokens[j]);
			}printf("\n");

			str[i] = '(';
		}
	}
}

char *handleExpression(char *const str, char **&brackets) {
	char *ret = 0; char *args[64] = {0}; int i = 1;

	while(*brackets != 0) {
		if(**brackets == '(') {
			ret = *brackets + 1;
			**brackets = '\0';
			brackets++;
			ret = handleExpression(ret, brackets);
		} else if(**brackets == ')') {
			ret = *brackets + 1;
			**brackets = '\0';
			brackets++;
			break;
		}
	}
	
	for(char *tok = strtok(str, " "); tok; tok = strtok(0, " ")) {
		args[i] = tok;
		i++;
	}
	
	handleTokens(args + i - 1);

	return 0;
}

int executeCommands(char ** argv) {
	printf("EXECUTING COMMAND: ");
	for(int i = 0; argv[i]; i++) {
		printf("%s ", argv[i]);
	} printf("\n");
	
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
	} else if(strcmp(*argv, "exit") == 0) {
		printf("End of Program\n");
		exit(0);
	}

	pid_t pid = fork();
	int status;
	if(pid < 0) {
		perror("forking child process failed\n");
		exit(0);
	} else if(pid == 0) {
		if(execvp(*argv, argv) < 0) {
			perror("exec failed\n");
			exit(0);
		}
	}
	while(wait(&status) != pid)
		;
	return 1;
}

int checkForFile(const char *const fileName, const char *const flags) {
	// -e => checks if file directory exists
	// -f => checks if file directory exists & is regular
	// -d => checks if file directory exists & is directory
	struct stat sb;
	if (stat(fileName, &sb) != 0) {
		printf("file does not exist\n");
		return 0;
	} else if(strcmp(flags, "-f") == 0) {
		if((sb.st_mode & S_IFMT) == S_IFREG) {
			printf("file exists and is regular\n");
			return 1;
		} else {
			printf("file is not regular\n");
			return 0;
		}
	} else if(strcmp(flags, "-d") == 0) {
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
	
	return 1;
}
