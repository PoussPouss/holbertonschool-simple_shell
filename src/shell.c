#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * main - Point d'entrée du programme shell
 *
 * Cette fonction implémente un shell simple qui lit les entrées utilisateur,
 * les analyse et exécute les commandes dans un processus enfant.
 *
 * Return: 0 en cas de succès, ou un code d'erreur en cas d'échec
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	while (1)
	{
		characters = read_command(&buffer, &bufsize);

		if (characters == -1)
			break;

		process_command(buffer);
	}

	free(buffer);
	return (0);
}
