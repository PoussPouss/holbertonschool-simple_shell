#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * 
 * 
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;
	pid_t child_pid;
	int status;
	char *argv[2];

	while (1)
	{
		printf("$ ");
		characters = getline(&buffer, &bufsize, stdin);

		if (characters == -1)
		{
			printf("\n");
			break;
		}

		if (buffer[characters - 1] == '\n')
			buffer[characters - 1] = '\0';

		if (strlen(buffer) == 0)
			continue;

		argv[0] = buffer;
		argv[1] = NULL;

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error:");
			continue;
		}

		if (child_pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror(argv[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(buffer);
	return (0);
}
