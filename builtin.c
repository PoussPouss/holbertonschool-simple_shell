#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

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

	return (0);
}

/**
 * handle_builtin_pid - Displays the current shell's process ID
 * @args: Command arguments (unused but freed)
 *
 * Return: Always EXIT_SUCCESS
 */
int handle_builtin_pid(char **args)
{
	int i;
	pid_t current_pid = getpid();

	printf("Current shell PID: %d\n", current_pid);

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);

	return (0);
}
