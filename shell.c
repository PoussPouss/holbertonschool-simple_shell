#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * main - Entry point of the shell program (version 0.2)
 *
 * This function implements a simple shell that reads user input,
 * parses it, searches for the command in PATH, and executes it.
 *
 * @argc: The number of command-line arguments
 * @argv: An array of strings representing the command-line arguments
 *
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char **argv)
{
	size_t bufsize = 0;
	ssize_t characters;
	char *prog_name, *buffer = NULL;
	int exit_status = EXIT_SUCCESS, is_interactive, cmd_count = 1;

	(void)argc;
	prog_name = argv[0];
	is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
			printf("$ ");

		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
			break;

		if (buffer[characters - 1] == '\n')
			buffer[characters - 1] = '\0';

		if (strlen(buffer) == 0)
			continue;

		exit_status = process_command(buffer, prog_name, cmd_count);

		if (exit_status == -1)
			break;

		cmd_count++;
	}
	free(buffer);
	return (exit_status);
}
