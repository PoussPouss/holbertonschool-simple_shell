#include <stddef.h>

/**
 * 
 * 
 */
char *read_line(void)
{}

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

	/* Première passe : compter les mots */
	tmp = strdup(str);
	token = strtok(tmp, " \t\n");

	while (token != NULL)
	{
		words++;
		token = strtok(NULL, " \t\n");
	}
	free(tmp);
	/* Allouer l'array */
	array = malloc(sizeof(char *) * (words + 1));

	if (array == NULL)
		return (NULL);
	/* Deuxième passe : remplir l'array */
	token = strtok(str, " \t\n");
	while (token != NULL)
	{
		array[i++] = _strdup(token);
		token = strtok(NULL, " \t\n");
	}
	array[i] = NULL;
	return (array);
}

/**
 * 
 * 
 */
void remove_comments(char *line)
{}