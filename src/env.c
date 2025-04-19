#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * _getenv - Récupère la valeur d'une variable d'environnement
 * @name: Nom de la variable d'environnement à rechercher
 *
 * Return: Pointeur vers la valeur de la variable, ou NULL si non trouvée
 */
char *_getenv(const char *name)
{
	int i;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (NULL);

	name_len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
			return (&environ[i][name_len + 1]);
	}
	return (NULL);
}

/**
 * find_env_index - Trouve l'index d'une variable d'environnement
 * @name: Nom de la variable à trouver
 *
 * Return: Index de la variable ou -1 si non trouvée
 */
int find_env_index(const char *name)
{
	int i;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (-1);
	 name_len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
			return (i);
	}
	return (-1);
}

/**
 * _setenv - Modifie ou ajoute une variable d'environnement
 * @name: Nom de la variable
 * @value: Valeur à assigner
 * @overwrite: Flag indiquant s'il faut écraser une variable existante
 *
 * Return: 0 en cas de succès, -1 en cas d'erreur
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	 int index, env_count, i;
	 char *new_entry, **new_environ;
	 size_t entry_len;

	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
		return (-1);

	 index = find_env_index(name);

	if (index >= 0 && overwrite == 0)
		return (0);

	 entry_len = strlen(name) + strlen(value) + 2;
	 new_entry = malloc(entry_len);
	if (new_entry == NULL)
		return (-1);
	sprintf(new_entry, "%s=%s", name, value);
	if (index >= 0)
	{
		free(environ[index]);
		environ[index] = new_entry;
		return (0);
	}
	env_count = 0;
	while (environ[env_count] != NULL)
		env_count++;

	 new_environ = malloc((env_count + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		free(new_entry);
		return (-1);
	}
	for (i = 0; i < env_count; i++)
		new_environ[i] = environ[i];

	new_environ[env_count] = new_entry;
	new_environ[env_count + 1] = NULL;
	environ = new_environ;
	return (0);
}

/**
 * _unsetenv - Supprime une variable d'environnement
 * @name: Nom de la variable à supprimer
 *
 * Return: 0 en cas de succès, -1 en cas d'erreur
 */
int _unsetenv(const char *name)
{
	int index, i;

	if (name == NULL || *name == '\0')
		return (-1);

	index = find_env_index(name);

	if (index == -1)
		return (0);

	free(environ[index]);

	for (i = index; environ[i] != NULL; i++)
	{
		environ[i] = environ[i + 1];
	}
	return (0);
}

/**
 * print_env - Affiche toutes les variables d'environnement
 */
void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
