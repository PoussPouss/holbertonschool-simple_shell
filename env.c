#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of the environment variable to search for
 *
 * Return: Pointer to the value of the variable, or NULL if not found
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
 * find_env_index - Finds the index of an environment variable
 * @name: Name of the variable to find
 *
 * Return: Index of the variable or -1 if not found
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
 * _setenv - Modifies or adds an environment variable
 * @name: Name of the variable
 * @value: Value to assign
 * @overwrite: Flag indicating whether to overwrite an existing variable
 *
 * Return: 0 on success, -1 on error
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
 * _unsetenv - Removes an environment variable
 * @name: Name of the variable to remove
 *
 * Return: 0 on success, -1 on error
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
 * print_env - Displays all environment variables
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
