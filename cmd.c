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
	/* Check if running in interactive mode */
	int interactive = isatty(STDIN_FILENO);

	if (interactive)
		write(STDOUT_FILENO, "$ ", 2); /* Only display prompt in interactive mode */

	characters = getline(buffer, bufsize, stdin); /* Read user input */

	if (characters == -1) /* EOF (Ctrl+D) detected */
	{
		if (interactive)
			write(STDOUT_FILENO, "\n", 1);
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
 * Return: Exit status of the command, 1 on fork error.
 */
int execute_command(char *command_path, char **args,
	char *prog_name, int cmd_count)
{
	pid_t child_pid;
	int status, exit_status = 0, i;

	child_pid = fork(); /* Create a child process */
	if (child_pid == -1)
	{
		perror("Error: fork failed");
		free(command_path);
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		return (1);
	}
	if (child_pid == 0) /* Child process */
	{
		if (execve(command_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: Permission denied\n",
					prog_name, cmd_count, args[0]);
			free(command_path);
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			exit(126); /* Permission denied exit code */
		}
	}
	else /* Parent process */
	{
		wait(&status);  /* Wait for child to finish */
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
	struct stat st;

	if (buffer == NULL || strlen(buffer) == 0)  /* Handle empty input */
		return (0);

	args = split_string(buffer); /* Split input into arguments */
	if (args == NULL) /* Memory allocation failed */
		return (1);

	if (args[0] == NULL) /* Empty arguments array (e.g., just spaces) */
	{
		free(args);
		return (0);
	}
	if (strcmp(args[0], "exit") == 0) /* Built-in: exit command */
	{
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		return (-1);
	}

	if (strcmp(args[0], "env") == 0) /* Built-in: env command */
		return (handle_builtin_env(args));

	if (strcmp(args[0], "pid") == 0) /* Built-in: pid command (bonus) */
		return (handle_builtin_pid(args));

	command_path = find_path_command(args[0]); /* Search PATH for command */
	if (command_path == NULL || (stat(command_path, &st) == 0 &&
	S_ISDIR(st.st_mode)))
	{
		error_code = command_error(args, prog_name, cmd_count, command_path);
		return (error_code);
	}
	return (execute_command(command_path, args, prog_name, cmd_count));
}

/**
 * command_error - Handles command not found errors
 * @args: Array of command arguments
 * @prog_name: Name of the program for error messages
 * @cmd_count: Command counter for error messages
 * @command_path: Full path of the command to check for errors
 *
 * Description: This function displays an appropriate error message
 * depending on whether the command contains a path or not.
 * It also frees the memory allocated for args.
 *
 * Return: Returns 2 for "No such file or directory"
 * or 127 for "not found" errors
 */
int command_error(char **args, char *prog_name, int cmd_count,
	char *command_path)
{
	int i, code_return;
	struct stat st;

	if (command_path && stat(command_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		fprintf(stderr, "%s: %d: %s: Is a directory\n",
				prog_name, cmd_count, args[0]);
		free(command_path);
		code_return = 126;  /* Same error code as permission denied */
	}

	else if (strchr(args[0], '/') != NULL) /* Check if command includes path */
	{
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
			prog_name, cmd_count, args[0]); /* File not found error */
		code_return = (2); /* Standard error code for file not found */
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: command not found\n",
			 prog_name, cmd_count, args[0]); /* Command not found error */
		code_return = (127); /* Standard error code for command not found */
	}

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);

	return (code_return);
}
