#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * This function implements a simple shell that reads user input,
 * parses it, and executes commands in a child process.
 *
 * Return: Always 0 on success, or an error code on failure.
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
		if (isatty(STDIN_FILENO))
			printf("$ ");

		characters = getline(&buffer, &bufsize, stdin);

	if (characters == -1)
	{
		if (isatty(STDIN_FILENO))
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
			if (execve(argv[0], argv, environ) == -1)
			{
				fprintf(stderr, "./hsh: No such file or directory\n");
				exit(1);
			}
		}
		else
			wait(&status);
	}
	free(buffer);
	return (0);
}
