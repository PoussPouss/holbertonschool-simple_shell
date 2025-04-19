#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
		array[i++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	array[i] = NULL;
	return (array);
}

/**
* read_line - Lit une ligne de commande depuis l'entrée standard
*
* Return: La ligne lue, ou NULL en cas d'erreur ou de fin de fichier (EOF)
*/
char *read_line(void)
{
	 char *line = NULL;

	 size_t bufsize = 0;
	 ssize_t characters;

	 /* Utilisation de getline pour lire une ligne complète */
	 characters = getline(&line, &bufsize, stdin);

	 /* Vérifier si EOF (Ctrl+D) ou erreur */
	if (characters == -1)
	{
		/* Libérer la mémoire allouée par getline en cas d'erreur */
		free(line);
		return (NULL);
	}

	/* Supprimer le caractère de nouvelle ligne à la fin */
	if (characters > 0 && line[characters - 1] == '\n')
		line[characters - 1] = '\0';

	return (line);
}
/**
* remove_comments - Supprime les commentaires d'une ligne de commande
* @line: La ligne à traiter
*
* Description: Cette fonction supprime la partie commentaire d'une ligne,
* c'est-à-dire tout ce qui suit le caractère '#'. Si le '#' est
* le premier caractère ou s'il est précédé d'un espace, il est considéré
* comme un début de commentaire.
*/
void remove_comments(char *line)
{
int i;


	if (line == NULL)
		return;

	for (i = 0; line[i] != '\0'; i++)
	{
		/* Détection d'un début de commentaire */
		if (line[i] == '#')
		{
			/* Si '#' est le premier caractère ou est précédé d'un espace */
			if (i == 0 || line[i - 1] == ' ' || line[i - 1] == '\t')
			{
				/* Remplacer le début du commentaire par la fin de chaîne */
				line[i] = '\0';
				break;
			}
		}
	}
}
