#include <stdio.h>
#include <string.h>
#include <unistd.h>
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

	/* Vérification des paramètres */
	if (name == NULL || *name == '\0')
		return (NULL);

	/* Longueur du nom de la variable */
	name_len = strlen(name);

	/* Parcourir l'environnement */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Vérifie si cette entrée commence par le nom recherché suivi de '=' */
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			/* Retourne un pointeur vers la valeur (juste après le '=') */
			return (&environ[i][name_len + 1]);
		}
	}

	/* Variable non trouvée */
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
		{
			return (i);
		}
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
	/* Vérification des arguments */
	if (name == NULL || *name == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	/* Vérifier si la variable existe déjà */
	 index = find_env_index(name);
	/* Si la variable existe et overwrite est 0, on ne fait rien */
	if (index >= 0 && overwrite == 0)
		return (0);
	/* Créer la nouvelle entrée name=value */
	 entry_len = _strlen(name) + _strlen(value) + 2; /* +2 pour '=' et '\0' */
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
	for (env_count = 0; environ[env_count] != NULL; env_count++)
		;
	 /* Créer un nouveau tableau environ avec un emplacement de plus */
	 new_environ = malloc((env_count + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		free(new_entry);
		return (-1);
	}
	/* Copier les anciennes variables */
	for (i = 0; i < env_count; i++)
		new_environ[i] = environ[i];
	/* Ajouter la nouvelle variable et le NULL final */
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
	/* Vérification des arguments */
	if (name == NULL || *name == '\0')
		return (-1);
	/* Trouver l'index de la variable à supprimer */
	index = _find_env_index(name);
	/* Si la variable n'existe pas, rien à faire */
	if (index == -1)
		return (0);
	/* Libérer la mémoire de la chaîne supprimée */
	free(environ[index]);
	/* Décaler toutes les variables suivantes */
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
