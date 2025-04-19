#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * read_command - Affiche le prompt et lit la commande de l'utilisateur
 * @buffer: Pointeur vers le buffer qui contiendra la commande
 * @bufsize: Pointeur vers la taille du buffer
 *
 * Return: Nombre de caractères lus, ou -1 si EOF
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
 * execute_command - Exécute une commande avec ses arguments
 * @command_path: Chemin complet de la commande à exécuter
 * @args: Tableau d'arguments de la commande
 *
 * Return: 0 en cas de succès, -1 en cas d'erreur
 */
int execute_command(char *command_path, char **args)
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
			fprintf(stderr, "./hsh: %s: No such file or directory\n", args[0]);
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
 * process_command - Traite la ligne de commande saisie
 * @buffer: La ligne de commande à traiter
 *
 * Return: 0 pour continuer l'exécution, -1 pour quitter
 */
int process_command(char *buffer)
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

