#include <stdio.h>
#include <string.h>

int main() {
	char str[] = "ls -a; cat main.cpp; echo hello world;";
	char *statements[1024] = {0};

	int i = 0;
	for(char *tok = strtok(str, ";"); tok; tok = strtok(0, ";"), i++) {
		statements[i] = tok;
		printf("token split by ';': %s\n", tok);
	}

	char *parsedTokens[1024] = {0};
	for(int i = 0; statements[i]; i++) {
		int j = 0;
		for(char *tok = strtok(statements[i], " "); tok; tok = strtok(0, " "), j++) {
			parsedTokens[j] = tok;
		}

		//call execute args here...
		//execute (*parsedTokens, parsedTokens)
		//

		for(int k = 0; parsedTokens[k]; k++)
			parsedTokens[k] = 0;
	}

	return 0;
}
