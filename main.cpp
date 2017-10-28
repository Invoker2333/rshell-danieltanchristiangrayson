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

int main() {
	char buffer[2048];
	while(1) {
		
		printf("Type in a command to execute: ");
		scanf("%s", buffer);

		if(strcmp(buffer, "exit") == 0) {
			printf("END\n");
			return 0;
		}
	
		if(executeCommands(buffer)) {
			printf("Commands successfully executed.\n");
		} else {
			printf("Commands failed\n");
		}
	}
}
