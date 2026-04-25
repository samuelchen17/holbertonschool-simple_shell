#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Structs */

/**
 * struct list_s - singly linked list
 * @dir_path: directory path
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s {
char *dir_path;
struct list_s* next;
} list_t;

/* Prototypes */
char *handle_path(char *cmd);

/* Helper prototypes */
void free_args_arr(char **args_arr);

/* Practice Prototypes */
int new_env_helper(const char *name, const char *value);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
list_t *add_node_end(list_t **head, char *token);
void print_environ(char **environ);
char *_getenv(const char *name);
list_t *tokenise_env_paths(void);

#endif
