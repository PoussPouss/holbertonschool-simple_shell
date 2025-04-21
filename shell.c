#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * This function implements a simple shell that reads user input,
 * parses it and executes commands in a child process.
 *
 * Return: 0 on success, or an error code on failure
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;
	char **args;

	while (1)
	{
		characters = read_command(&buffer, &bufsize);

		if (characters == -1)
			break;
		args = split_string(buffer);

		if (args != NULL && check_builtin(args))
		{
			if (args[0] && strcmp(args[0], "exit") == 0)
			{
			free(args);
			break;
			}
			/* Si c'est "env" ou un autre built-in, on continue la boucle */
			free(args);
			continue;
		}

		if (args != NULL)
		free(args);

		if (process_command(buffer) == -1)
			break;
	}

	free(buffer);
	return (0);
}
