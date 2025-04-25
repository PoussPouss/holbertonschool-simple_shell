#include "shell.h"

/**
 * main - Entry point of the hsh program
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
	int exit_status, cmd_count = 1;

	(void)argc;
	prog_name = argv[0];

	signal(SIGINT, handle_sigint);	/* Set signal handler for Ctrl+C */

	while (1)
	{
		characters = read_command(&buffer, &bufsize);	/* Read user input */

		if (characters == -1)	/* EOF (Ctrl+D) detected */
			break;

		if (strlen(buffer) == 0) /* Skip empty commands */
			continue;

		/* Process and execute the command */
		exit_status = process_command(buffer, prog_name, cmd_count);

		if (exit_status == -1)	/* Exit command was entered */
		{
			free(buffer);
			_exit(0);
		}

		cmd_count++;	/* Increment command counter */
	}
	free(buffer);
	return (exit_status);	/* Return exit status of last command */
}
