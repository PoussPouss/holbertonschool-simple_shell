#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "path.h"

/**
 * build_path_list - Builds a linked list of directories from PATH environment
 *
 * Return: Pointer to the head of the linked list, or NULL on failure
 */
path_node_t *build_path_list(void)
{
	char *path_value, *token, *path_copy;
	path_node_t *head = NULL, *new_node;


	path_value = _getenv("PATH");
	if (path_value == NULL)
		return (NULL);

	path_copy = strdup(path_value);
	if (path_copy == NULL)
		return (NULL);

	token = strtok(path_copy, ':');
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

		new_node->next = head;
		head = new_node;

		token = strtok(NULL, ':');
	}

	free(path_copy);
	return (head);
}

/**
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
