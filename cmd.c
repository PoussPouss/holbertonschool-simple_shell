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
		printf("$ ");

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
int execute_command(char *command_path, char **args,
	char *prog_name, int cmd_count)
{
	pid_t child_pid;
	int status, exit_status = 0, i;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: fork failed");
		free(command_path);
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: Cannot execute\n",
					prog_name, cmd_count, args[0]);
			free(command_path);
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			exit(126);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);

		free(command_path);
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
	}
	return (exit_status);
}

/**
 * process_command - Processes and executes a command from the user input
 * @buffer: The input command string
 * @prog_name: The name of the shell program
 * @cmd_count: The command count for error messages
 *
 * Return: 0 on success, -1 to exit, or 0 if the command is not found
 */
int process_command(char *buffer, char *prog_name, int cmd_count)
{
	char **args, *command_path;
	int error_code, i = 0;

	if (buffer == NULL || strlen(buffer) == 0)
		return (0);

	args = split_string(buffer);
	if (args == NULL)
		return (1);

	if (args[0] == NULL)
	{
		free(args);
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
		return (handle_builtin_env(args));

	if (strcmp(args[0], "pid") == 0)
		return (handle_builtin_pid(args));

	command_path = find_path_command(args[0]);
	if (command_path == NULL)
	{
		error_code = command_error(args, prog_name, cmd_count);
		return (error_code);
	}
	return (execute_command(command_path, args, prog_name, cmd_count));
}

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
	int i, code_return;

	if (strchr(args[0], '/') != NULL)
	{
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
			prog_name, cmd_count, args[0]);
		code_return = (2);
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			 prog_name, cmd_count, args[0]);
		code_return = (127);
	}

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);

	return (code_return);
}
