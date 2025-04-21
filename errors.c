#include <stdio.h>

/**
 * command_error - Handles command not found errors
 * @args: Array of command arguments
 * @prog_name: Name of the program for error messages
 * @cmd_count: Command counter for error messages
 *
 * Description: This function displays an appropriate error message
 * depending on whether the command contains a path or not.
 * It also frees the memory allocated for args.
 *
 * Return: Always returns 0
 */

int command_error(char **args, char *prog_name, int cmd_count)
{
	int i;

	if (strchr(args[0], '/') != NULL)
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
			prog_name, cmd_count, args[0]);
	else
		fprintf(stderr, "%s: %d: %s: Command Not Found\n",
			prog_name, cmd_count, args[0]);

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);

	return (0);
}
