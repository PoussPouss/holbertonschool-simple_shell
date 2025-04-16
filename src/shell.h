#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct command - Represents a shell command and its arguments
 * @args: Array of arguments for the command
 * @arg_count: Number of arguments in the command
 */
typedef struct command
{
	char **args;       /* Arguments de la commande */
	int arg_count;     /* Nombre d'arguments */
} command_t;

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

/* Gestion des variables d'environnement */
char *_getenv(const char *name);
int _find_env_index(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void print_env(void);
int print_path_directories(void);

/* Manipulation des chemins PATH */
path_node_t *add_node_end(path_node_t **head, char *directory);
path_node_t *build_path_list(void);
void free_path_list(path_node_t *head);
void print_path_list(const path_node_t *head);

/* Fonctions principales du shell */
int main(void);
void shell_loop(void);

/* Gestion des processus */
pid_t fork(void);
int execve(const char *filename, char *const argv[], char *const envp[]);
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);

/* Parsing et traitement des arguments */
char *read_line(void);
char **split_string(char *str);
void remove_comments(char *line);

/* Utilitaires pour les fichiers */
int _which(char *filename);

/* Fonctions standard réimplémentées */
char *strdup(const char *s);
char *strtok(char *str, const char *delim);

#endif
