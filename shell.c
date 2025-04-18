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

	while (1)
	{
		characters = read_command(&buffer, &bufsize);

		if (characters == -1)
			break;

		process_command(buffer);
	}

	free(buffer);
	return (0);
}
