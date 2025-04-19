<<<<<<< HEAD
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "path.h"

/**
 * build_path_list - Builds a linked list of directories from PATH environment
 *
 * Return: Pointer to the head of the linked list, or NULL on failure
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * build_path_list - Builds a linked list of
 * directories from the PATH environment variable.
 *
 * Return: A pointer to the head of the linked list, or NULL on failure.
>>>>>>> origin/main
 */
path_node_t *build_path_list(void)
{
	char *path_value, *token, *path_copy;
	path_node_t *head = NULL, *new_node;

<<<<<<< HEAD

=======
>>>>>>> origin/main
	path_value = _getenv("PATH");
	if (path_value == NULL)
		return (NULL);

	path_copy = strdup(path_value);
	if (path_copy == NULL)
		return (NULL);

<<<<<<< HEAD
	token = strtok(path_copy, ':');
=======
	token = strtok(path_copy, ":");

>>>>>>> origin/main
	while (token != NULL)
	{
		new_node = malloc(sizeof(path_node_t));
		if (new_node == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		new_node->directory = strdup(token);
		if (new_node->directory == NULL)
		{
			free(new_node);
			free(path_copy);
			return (NULL);
		}
<<<<<<< HEAD

		new_node->next = head;
		head = new_node;

		token = strtok(NULL, ':');
	}

=======
		new_node->next = head;
		head = new_node;
		token = strtok(NULL, ":");
	}
>>>>>>> origin/main
	free(path_copy);
	return (head);
}

/**
<<<<<<< HEAD
 * print_path_directories - Affiche chaque répertoire du PATH, un par ligne
 *
 * Return: 0 en cas de succès, 1 si PATH n'existe pas
 */
int print_path_directories(void)
{
	char *path, *path_copy, *dir;

	/* Récupérer la variable d'environnement PATH */
	path = _getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "PATH variable not found\n");
		return (1);
	}

	 /* Dupliquer la chaîne PATH pour la manipulation avec strtok */
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		return (1);
	}

	/* Séparer la chaîne PATH en utilisant ":" comme délimiteur */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		printf("%s\n", dir);
		dir = strtok(NULL, ":");
	}

	/* Libérer la mémoire allouée */
	free(path_copy);

	return (0);
}
=======
 * print_path_list - Prints the directories in the linked list of PATH.
 * @head: Pointer to the head of the linked list.
 *
 * Description: Iterates through the linked list of directories and prints
 * each directory to the standard output.
 *
 * Return: 0 on success, or 1 if an error occurs.
 */
int print_path_list(const path_node_t *head)
{
	const path_node_t *current;

	if (head == NULL)
	{
		fprintf(stderr, "Path list is empty\n");
		return (1);
	}

	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->directory);
		current = current->next;
	}

	return (0);
}

/**
 * print_path_directories - Prints the directories
 * in the PATH environment variable.
 *
 * Return: 0 on success, or -1 on failure.
 */
int print_path_directories(void)
{
	char *path_value, *token, *path_copy;
	path_node_t *head = NULL, *new_node;
	int result;

	path_value = _getenv("PATH");
	if (path_value == NULL)
		return (-1);

	path_copy = strdup(path_value);
	if (path_copy == NULL)
		return (-1);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		new_node = malloc(sizeof(path_node_t));
		if (new_node == NULL)
		{
			free(path_copy);
			return (-1);
		}

		new_node->directory = strdup(token);
		if (new_node->directory == NULL)
		{
			free(new_node);
			free(path_copy);
			return (-1);
		}
		new_node->next = head;
		head = new_node;
		token = strtok(NULL, ":");
	}
	free(path_copy);

	result = print_path_list(head);

	free_path_list(head);

	return (result);
}

/**
 * find_path_command - Searches for a command in the PATH directories
 * @command: The command to find
 *
 * Description: This function searches for the given command in the directories
 * listed in the PATH environment variable. If the command is found and is
 * executable, it returns the full path to the command. If the command is not
 * found, it returns NULL.
 *
 * Return: Full path if found, NULL otherwise
 */
char *find_path_command(char *command)
{
	path_node_t *path_list, *current;
	char *full_path;
	struct stat st;

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
			return (strdup(command));
		return (NULL);
	}

	path_list = build_path_list();
	if (!path_list)
		return (NULL);

	current = path_list;
	while (current)
	{
		full_path = malloc(strlen(current->directory) + strlen(command) + 2);
		if (!full_path)
			return (NULL);

		sprintf(full_path, "%s/%s", current->directory, command);

		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			return (full_path);
		}

		free(full_path);
		current = current->next;
	}
	return (NULL);
}

/**
 * free_path_list - Frees a linked list of path directories
 * @head: Pointer to the head of the linked list
 *
 * Description: This function iterates through the linked list and frees
 * both the directory string and the node structure for each element.
 */
void free_path_list(path_node_t *head)
{
	path_node_t *current, *next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->directory);
		free(current);
		current = next_node;
	}
}
>>>>>>> origin/main
