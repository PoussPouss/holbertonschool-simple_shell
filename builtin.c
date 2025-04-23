#include "shell.h"

/**
 * handle_builtin_env - Handles the env built-in command
 * @args: Array of command arguments
 *
 * Description: This function implements the env built-in command
 * that prints the current environment. It frees memory
 * allocated for the arguments before returning.
 *
 * Return: Always returns 0 on success
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
 * Return: Always returns 0 on success
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

/**
 * handle_builtin_exit - Handles the exit built-in command with arguments
 * @args: Array of command arguments
 * @prog_name: Name of the program for error messages
 * @cmd_count: Command counter for error messages
 *
 * Description: This function processes the exit command and its optional
 * numeric argument. If no argument is provided, it returns -1 to signal
 * normal shell exit. If a numeric argument is provided, it exits with
 * that status code. If an invalid argument is provided, it prints an
 * error message and returns an error code.
 *
 * Return: -1 for normal exit without argument, exits with status
 * for valid numeric argument, 2 for invalid argument
 */
int handle_builtin_exit(char **args, char *prog_name, int cmd_count)
{
	int status = 0;
	int i, j;

	/* Check if exit has an argument */
	if (args[1] != NULL)
	{
		/* Validate that the argument is a valid number */
		for (j = 0; args[1][j] != '\0'; j++)
		{
			if (args[1][j] < '0' || args[1][j] > '9')
			{
				fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
						prog_name, cmd_count, args[1]);

				/* Free memory before returning */
				for (i = 0; args[i]; i++)
					free(args[i]);
				free(args);

				return (2);  /* Standard error code for incorrect usage */
			}
		}
		/* Convert string to integer */
		for (j = 0; args[1][j] != '\0'; j++)
		{
			status = status * 10 + (args[1][j] - '0');
		}
	}
	/* Free memory */
	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);

	if (status == 0)
		return (-1);  /* Special code for normal shell exit */
	exit(status);  /* Exit with specified status code */
}
