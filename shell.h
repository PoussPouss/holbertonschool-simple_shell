#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <signal.h>
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

/* env.c - Environment variable functions */
char *_getenv(const char *name);
int find_env_index(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void print_env(void);

/* path.c - PATH handling functions */
path_node_t *build_path_list(void);
int print_path_list(const path_node_t *head);
int print_path_directories(void);
char *find_path_command(char *command);
void free_path_list(path_node_t *head);

/* cmd.c - Command processing functions */
ssize_t read_command(char **buffer, size_t *bufsize);
int execute_command(char *command_path, char **args, char *prog_name,
	int cmd_count);
int process_command(char *buffer, char *prog_name, int cmd_count);
int command_error(char **args, char *prog_name, int cmd_count);
void handle_builtin_exit(char **args);

/* parser.c - String parsing functions */
char **split_string(char *str);
int _which(char *filename);

/* signal.c - Signal handling functions */
void handle_sigint(int sig);

/* builtin.c - Built-in command functions */
int handle_builtin_env(char **args);
int handle_builtin_pid(char **args);

#endif
