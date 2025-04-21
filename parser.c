#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * split_string - Splits a string into an array of words.
 * @str: The input string to be split.
 *
 * Return: A pointer to an array of strings (words),
 * or NULL if an error occurs.
 */
char **split_string(char *str)
{
	char **array;
	char *token;
	int i = 0;
	int words = 0;
	char *tmp;

	if (str == NULL)
		return (NULL);

	tmp = strdup(str);
	token = strtok(tmp, " \t\n");

	while (token != NULL)
	{
		words++;
		token = strtok(NULL, " \t\n");
	}
	free(tmp);
	array = malloc(sizeof(char *) * (words + 1));

	if (array == NULL)
		return (NULL);

	token = strtok(str, " \t\n");
	while (token != NULL)
	{
		array[i++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	array[i] = NULL;
	return (array);
}

/**
 * _which - Checks if a command exists in the PATH
 * @filename: The command to check
 *
 * Return: 0 if found, -1 otherwise
 */
int _which(char *filename)
{
	char *path = find_path_command(filename);

	if (path != NULL)
	{
		printf("%s\n", path);
		free(path);
		return (0);
	}
	return (-1);
}
