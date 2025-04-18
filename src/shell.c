#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "shell.h"

/**
 * 
 * 
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	printf("$ ");
	nread = getline(&line, &len, stdin);

	if (nread != -1)
	{
		printf("%s", line);
	}
	else
	{
		printf("\n");
	}

	free(line);
	return (0);
}
