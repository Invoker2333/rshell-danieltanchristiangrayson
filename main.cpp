#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstdlib>

// return 1 if successful, return 0 if NOT successful
int executeCommands(char ** argv) {
	pid_t pid;
	int status;

	if((pid = fork()) < 0)
		exit(1);
	else if(pid == 0) {
		execvp(*argv, argv);
		exit(1);
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

int main() {
	std::basic_string<char> buffer;
	char *temp = 0;

	while(1) {
		printf("$: ");
		std::getline(std::cin, buffer);
		temp = (char *)malloc((int)sizeof(char) * (int)buffer.length() + (int)sizeof(char));// + sizeof(char) to account for NULL-termination...
		strcpy(temp, buffer.c_str());		

		if(strcmp(temp, "exit") == 0) {
			printf("End of program.\n");
			free(temp);
			return 0;
		}
		
		handleCommands(temp);
		free(temp);
	}
}
