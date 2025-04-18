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
int find_env_index(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void print_env(void);

/* Manipulation des chemins PATH */
path_node_t *build_path_list(void);
void print_path_list(const path_node_t *head);
int print_path_directories(void);

/* Fonctions principales du shell */
void shell_loop(void);

/* Parsing et traitement des arguments */
char *read_line(void);
char **split_string(char *str);
void remove_comments(char *line);


/* Utilitaires pour les fichiers */
int _which(char *filename);


#endif
