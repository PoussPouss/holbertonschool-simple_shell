#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * This function implements a simple shell that reads user input,
 * parses it, searches for the command in PATH, and executes it.
 *
 * @argc: The number of command-line arguments
 * @argv: An array of strings representing the command-line arguments
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char **argv)
 {
	 char *buffer = NULL;  /* Ajoutez cette ligne pour déclarer buffer */
	 size_t bufsize = 0;
	 ssize_t characters;
	 char **args;
	 int is_interactive = isatty(STDIN_FILENO);  /* Ajoutez cette ligne */
	 /* Pour éviter les warnings de paramètres non utilisés */
	 (void)argc;
	 (void)argv;
	while (1)
	{
		if (is_interactive)
			write(STDOUT_FILENO, "$ ", 2);
		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
			break;
		args = split_string(buffer);
		if (args != NULL && args[0] != NULL)
		{
			/* Vérifier directement si c'est "exit" avant tout autre traitement */
			if (strcmp(args[0], "exit") == 0)
			{
				free(args);
				break;
			}
			else if (check_builtin(args))
			{
				free(args);
				continue;
			}
		free(args);
		}
		else if (args != NULL)
		{
			free(args);
		}
		if (process_command(buffer) == -1)
			break;
	}
		free(buffer);
		return (0);
}
