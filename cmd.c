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
*
* Return: 0 on success, -1 on error
*/
int execute_command(char *command_path, char **args)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror("Error");
			exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		free(command_path);
	}
	return (0);
}

/**
* process_command - Processes the input command line
* @buffer: The command line to process
*
* Return: 0 to continue execution, -1 to exit
*/
int process_command(char *buffer)
{
	char **args;

	char *command_path;

	int i;

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
	command_path = find_path_command(args[0]);
	if (command_path == NULL)
	{
	fprintf(stderr, "./hsh: %s: command not found\n", args[0]);
	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
	return (0);
	}

	return (execute_command(command_path, args));
}

/**
*check_builtin - Vérifie si la commande est un built-in et l'exécute
* @args: Tableau d'arguments de la commande
*
*Return: 1 si c'est un built-in exécuté, 0 sinon
*/
int check_builtin(char **args)
{
	int i;

	/* Ne pas traiter "exit" ici, c'est fait dans main */
	if (args[0] && strcmp(args[0], "exit") == 0)
		return (0);  /* Retourne 0 pour que main gère "exit" */

	/* Check si la commande est env */
	if (args[0] && strcmp(args[0], "env") == 0)
	{
		/*Print environnement variables */
		for (i = 0; environ[i] != NULL; i++)
		{
			/* Imprime chaques variables d'environnement */
			printf("%s\n", environ[i]);
		}
		return (1);
	}

	/* Ce n'est pas un built-in reconnu */
	return (0);
}
