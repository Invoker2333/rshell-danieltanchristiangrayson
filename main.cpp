#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>

// return 1 if successful
// return 0 if NOT successful
int executeCommands(char ** argv) {
	pid_t pid;
	int status;

	if((pid = fork()) < 0)
		return 0;
	else if(pid == 0)
		return execvp(*argv, argv) < 0? 0 : 1;
	while(waitpid(pid , &status, 0) != pid)
		;
	printf("Execution successful");
	return 1;
}

void handleCommands(char *commands) {
	char *statements[1024] = {0};

	int i = 0;
	for(char *tok = strtok(commands, ";"); tok; tok = strtok(0, ";")) {
		statements[i] = tok;
		i++;
		//printf("token split by ';': %s\n", tok);
	}

	char *parsedTokens[1024] = {0};
	for(int i = 0; statements[i]; i++) {
		int j = 0;
		for(char *tok = strtok(statements[i], " "); tok; tok = strtok(0, " ")) {
			parsedTokens[j] = tok;
			j++;
		}
		
		//call execute args here...
		if(!executeCommands(parsedTokens)) {
			printf("COMMAND_FAILED_EXECUTIONS...\n");
		}
		
		for(int l = 0; statements[i][l]; l++) {
			if(statements[i][l] == '#') return;
		}

		for(int k = 0; parsedTokens[k]; k++) {
			parsedTokens[k] = 0;
		}
	}
	
}


int main() {
	std::basic_string<char> buffer;
	char *temp = 0;	

	while(1) {
		printf("$: ");
		std::getline(std::cin, buffer);
		temp = (char *)buffer.c_str();		

		if(strcmp(temp, "exit") == 0) {
			printf("End of program.\n");
			return 0;
		}
		
		handleCommands(temp);

	}
}
