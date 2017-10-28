#include <stdio.h>

int main() {
	FILE *f = popen("ls", "r");
	char buffer[1024];
	
	if(!f) {
		printf("There were errors");
		return -1;
	}
	//while(fgets(buffer, sizeof(buffer), f)) {
	//	printf("%s", buffer);
	//}
	
	pclose(f);
}
