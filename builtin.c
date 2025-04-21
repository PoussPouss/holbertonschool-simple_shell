#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * handle_exit_status - Handles various exit statuses
 * @status: The exit status to handle
 * @is_interactive: Whether the shell is running in interactive mode
 *
 * Return: The original status
 */
int handle_exit_status(int status, int is_interactive)
{
	(void)is_interactive; /* Unused parameter */
	return (status);
}

/**
 * handle_builtin_env - Handles the env built-in command
 * @args: Array of command arguments
 *
 * Description: This function implements the env built-in command
 * that prints the current environment. It frees memory
 * allocated for the arguments before returning.
 *
 * Return: 0 on success
 */
int handle_builtin_env(char **args)
{
	int i;

	print_env();

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);

	return (EXIT_SUCCESS);
}
