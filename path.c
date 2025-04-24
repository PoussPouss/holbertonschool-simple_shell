#include "shell.h"

/**
 * build_path_list - Builds a linked list of
 * directories from the PATH environment variable.
 *
 * Return: A pointer to the head of the linked list, or NULL on failure.
 */
path_node_t *build_path_list(void)
{
	char *path_value, *token, *path_copy;
	path_node_t *head = NULL, *new_node;

	path_value = _getenv("PATH");  /* Get PATH environment variable */
	if (path_value == NULL)
		return (NULL);  /* PATH not found */

	path_copy = strdup(path_value);  /* Make a copy to avoid modifying original */
	if (path_copy == NULL)
		return (NULL);  /* Memory allocation failed */

	token = strtok(path_copy, ":");  /* Split path by colons */

	while (token != NULL)  /* Process each directory in PATH */
	{
		new_node = malloc(sizeof(path_node_t));
		if (new_node == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		new_node->directory = strdup(token);  /* Copy directory path */
		if (new_node->directory == NULL)  /* Check allocation success */
		{
			free(new_node);  /* Free node if directory allocation failed */
			free(path_copy);
			return (NULL);
		}
		new_node->next = head;  /* Add to front of list (reverse order) */
		head = new_node;  /* Update head pointer */
		token = strtok(NULL, ":");  /* Get next directory */
	}
	free(path_copy);
	return (head);
}

/**
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
	path_node_t *head;
	int result;

	head = build_path_list();
	if (head == NULL)
		return (-1);

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

	if (strchr(command, '/') != NULL)  /* Command contains path separator */
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
			return (strdup(command));  /* Return copy of command as-is */
		return (NULL);  /* Not found or not executable */
	}
	path_list = build_path_list();  /* Build path list */
	if (!path_list)
		return (NULL);  /* Failed to build path list */

	current = path_list;  /* Start at first node */
	while (current)  /* Try each directory */
	{
		full_path = malloc(strlen(current->directory) + strlen(command) + 2);
		if (!full_path)
		{
			free_path_list(path_list);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", current->directory, command);

		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free_path_list(path_list);  /* Free the path list */
			return (full_path);
		}

		free(full_path);
		current = current->next;  /* Move to next directory */
	}
	free_path_list(path_list);  /* Clean up path list */
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
