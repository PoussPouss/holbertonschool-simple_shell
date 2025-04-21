#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * handle_builtin_exit - Handles the exit built-in command
 * @args: Array of command arguments
 *
 * Description: This function implements the exit built-in command
 * that exits the shell. It does not handle any arguments.
 * It frees memory allocated for the arguments before exiting.
 *
 * Return: Does not return, calls exit() directly
 */
int handle_builtin_exit(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
		free(args[i]);

	free(args);
	exit(EXIT_SUCCESS);
}
