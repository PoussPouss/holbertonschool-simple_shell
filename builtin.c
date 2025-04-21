#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	return (EXIT_SUCCESS);
}

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
void handle_builtin_exit(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
		free(args[i]);

	free(args);
	exit(EXIT_SUCCESS);
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

	return (EXIT_SUCCESS);
}
