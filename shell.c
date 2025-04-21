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
 * @argc: The number of command-line arguments
 * @argv: An array of strings representing the command-line arguments
 *
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char **argv)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;
	int cmd_count = 1;
	char *prog_name;

	(void)argc;
	prog_name = argv[0];

	while (1)
	{
		characters = read_command(&buffer, &bufsize);

		if (characters == -1)
			break;

		if (process_command(buffer, prog_name, cmd_count) == -1)
			break;

		cmd_count++;
	}

	free(buffer);
	return (0);
}
