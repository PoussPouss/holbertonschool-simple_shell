#include "shell.h"
/**
 * remove_quotes - Removes surrounding quotes from a string if present
 * @str: The string to process
 *
 * Return: A new string without the quotes, or NULL if memory allocation fails
 * The caller is responsible for freeing the returned string
 */
char *remove_quotes(char *str)
{
	size_t len;
	char *result;

	if (str == NULL)
		return (NULL);

	len = strlen(str);

	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') ||
		(str[0] == '\'' && str[len - 1] == '\'')))
	{
		result = malloc(len - 1);
		if (result == NULL)
			return (NULL);

		strncpy(result, str + 1, len - 2);
		result[len - 2] = '\0';
		return (result);
	}
	return (strdup(str));
}

/**
 * split_string - Splits a string into an array of words.
 * @str: The input string to be split.
 *
 * Return: A pointer to an array of strings (words),
 * or NULL if an error occurs.
 */
char **split_string(char *str)
{
	char **array, *token, *token_no_quotes, *tmp;
	int words = 0, i = 0;

	if (str == NULL)
		return (NULL);
		tmp = strdup(str);
	if (tmp == NULL)
		return (NULL);
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
		token_no_quotes = remove_quotes(token);
		if (token_no_quotes == NULL)
		{
			array[i] = malloc(strlen(token) - 1);
			if (array[i] == NULL)
			{
				while (i > 0)
				{
					i--;
					free(array[i]);
				}
				free(array);
				return (NULL);
			}
			src = token + 1;
			dst = array[i];
			while (*src && *src != token[0])
				*dst++ = *src++;
			*dst = '\0';
		}
		else
		{
			array[i] = strdup(token);
			if (array[i] == NULL)
			{
				while (i > 0)
				{
					i--;
					free(array[i]);
				}
				free(array);
				return (NULL);
			}
		}
		array[i] = token_no_quotes;
		i++;
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
