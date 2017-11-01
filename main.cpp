#include <stdio.h>
#include <string.h>

int executeCommands(const char *const NAME) {
	FILE *file = popen(NAME, "r");
	char buffer[1024];

	if(file == 0)
		return 0;

	while(fgets(buffer, sizeof(buffer), file)) {
		printf("%s", buffer);
	}
	
	pclose(file);
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
	
	for(int i = 0; statements[i]; i++) {
		printf("Executing %s...\n", statements[i]);

		executeCommands(statements[i]);

		// this is to handle comments that begin w/ '#'
		for(int j = 0; statements[i][j]; j++) {
			if(statements[i][j] == '#')
				return;
		}
	}
	
	/* TODO: perhaps in the future, this would be useful???
	char *parsedTokens[1024] = {0};
	for(int i = 0; statements[i]; i++) {
		int j = 0;
		for(char *tok = strtok(statements[i], " "); tok; tok = strtok(0, " ")) {
			parsedTokens[j] = tok;
		}
		
		//call execute args here...
		//execute commands...
		//

		for(int k = 0; parsedTokens[k]; k++) {
			parsedTokens[k] = 0;
		}
	}
	*/
	
}


int main() {
	char buffer[2048] = {0};

	while(1) {
		printf("$: ");
		gets(buffer);

		if(strcmp(buffer, "exit") == 0) {
			printf("End of program.\n");
			return 0;
		}

		handleCommands(buffer);

	}
}
