#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * handle_exit_status - Handles various exit statuses and displays
 * appropriate messages
 * @status: The exit status to handle
 * @is_interactive: Whether the shell is running in interactive mode
 *
 * Return: EXIT_SUCCESS if the shell should exit, the original status otherwise
 */
int handle_exit_status(int status, int is_interactive)
{
	if (status == -1)
	{
		if (is_interactive)
			printf("Exiting shell.\n");
		return (EXIT_SUCCESS);
	}
	else if (status > 0)
	{
		if (is_interactive)
		{
			if (status == EXIT_ALLOCATION_ERROR)
				fprintf(stderr, "Memory allocation error occurred\n");
		}
	}
	return (status);
}
