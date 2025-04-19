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
	int status, i;
	char **args;
	char *command_path;

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

		args = split_string(buffer);
		if (args == NULL || args[0] == NULL)
		{
			if (args)
				free(args);
			fprintf(stderr, "Memory allocation error\n");
			continue;
		}
		command_path = find_path_command(args[0]);
        if (command_path == NULL)
        {
            fprintf(stderr, "./hsh: %s: command not found\n", args[0]);
            for (i = 0; args[i]; i++)
                free(args[i]);
            free(args);
            continue;
        }

		child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error:");
            free(command_path);
            for (i = 0; args[i]; i++)
                free(args[i]);
            free(args);
            continue;
        }
		if (child_pid == 0)
		{
			if (execve(command_path, args, environ) == -1)
			{
				fprintf(stderr, "./hsh: %s: No such file or directory\n", args[0]);
				free(command_path);
				for (i = 0; args[i]; i++)
					free(args[i]);
				free(args);
				exit(1);
			}
		}
		else
		{
			wait(&status);
			free(command_path);
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
		}
	}
	free(buffer);
	return (0);
}
