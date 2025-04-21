#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * read_command - Displays the prompt and reads the user command
 * @buffer: Pointer to the buffer that will contain the command
 * @bufsize: Pointer to the buffer size
 *
 * Return: Number of characters read, or -1 if EOF
 */
ssize_t read_command(char **buffer, size_t *bufsize)
{
	ssize_t characters;

	if (isatty(STDIN_FILENO))
		printf("($) ");

	characters = getline(buffer, bufsize, stdin);

	if (characters == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		return (-1);
	}

	if ((*buffer)[characters - 1] == '\n')
		(*buffer)[characters - 1] = '\0';

	return (characters);
}

/**
 * execute_command - Executes a command with its arguments
 * @command_path: Full path of the command to execute
 * @args: Array of command arguments
 * @prog_name: Name of the program for error messages
 * @cmd_count: Command counter for error messages
 *
 * Return: 0 on success, -1 on error
 */
int execute_command(char *command_path, char **args, char *prog_name,
	int cmd_count)
{
	pid_t child_pid;
	int status, i;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		free(command_path);
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		return (-1);
	}

	if (child_pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", prog_name, cmd_count, args[0]);
			free(command_path);
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			exit(1);
		}
	}
	else
	{
		wait(&status);
		free(command_path);
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
	}
	return (0);
}

/**
 * process_command - Processes the input command line
 * @buffer: The command line to process
 * @prog_name: Name of the program for error messages
 * @cmd_count: Command counter for error messages
 *
 * Return: 0 to continue execution, -1 to exit
 */
int process_command(char *buffer, char *prog_name, int cmd_count)
{
	char **args;
	char *command_path;
	int i;

	if (strlen(buffer) == 0)
		return (0);
	args = split_string(buffer);
	if (args == NULL || args[0] == NULL)
	{
		if (args)
			free(args);
		fprintf(stderr, "Memory allocation error\n");
		return (0);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		return (-1);
	}
	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		return (0);
	}
	command_path = find_path_command(args[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, cmd_count, args[0]);
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		return (0);
	}
	return (execute_command(command_path, args, prog_name, cmd_count));
}
