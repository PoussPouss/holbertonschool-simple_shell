#ifndef SHELL_H
#define SHELL_H
#define EXIT_SUCCESS 0
#define EXIT_ERROR 1
#define EXIT_CMD_NOT_FOUND 127
#define EXIT_CMD_CANNOT_EXECUTE 126
#define EXIT_INVALID_ARG 2
#define EXIT_ALLOCATION_ERROR 3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct path_node - Represents a node in a linked list of directories
 * @directory: The directory path
 * @next: Pointer to the next node in the list
 */
typedef struct path_node
{
	char *directory;
	struct path_node *next;
} path_node_t;

char *_getenv(const char *name);
int find_env_index(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void print_env(void);

path_node_t *build_path_list(void);
int print_path_list(const path_node_t *head);
int print_path_directories(void);
char *find_path_command(char *command);
void free_path_list(path_node_t *head);

ssize_t read_command(char **buffer, size_t *bufsize);
int execute_command(char *command_path, char **args, char *prog_name,
	int cmd_count);
int process_command(char *buffer, char *prog_name, int cmd_count);
int command_error(char **args, char *prog_name, int cmd_count);

char **split_string(char *str);
int _which(char *filename);
int handle_exit_status(int status, int is_interactive);
int handle_builtin_exit(char **args);
int handle_builtin_env(char **args);

#endif
