//This program experiments w/ piping

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
	int fd[2];
	int nbytes;
	char string[] = "Hello World!\n";
	char readBuffer[80];
	pid_t childpid;

	pipe(fd);


	if((childpid = fork()) == -1)
	{
		perror("fork error\n");
		return 1;
	}

	if(childpid == 0)

	{
		close(fd[0]);
		
		
		
		write(fd[1], string, strlen(string) + 1);
		printf("Writing: fd[0]: %d, fd[1]: %d\n", fd[0], fd[1]);

		return 0;

	}
	
	else

	{
		close(fd[1]);

		nbytes = read(fd[0], readBuffer, sizeof(readBuffer));

		printf("fd[0]: %d, fd[1]: %d\n", fd[0], fd[1]);
		printf("Received string: %s\nLength: %d\n", readBuffer, nbytes);

	}


	return 0;


}
