#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
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
		printf("%s: command not found\n", line);
	}

	free(line);
	return (0);
}
