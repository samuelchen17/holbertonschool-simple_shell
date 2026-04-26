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
typedef struct list_s
{
char *dir_path;
struct list_s *next;
} list_t;

/* Prototypes */
char *handle_path(char *cmd);

/* Helper prototypes */
void free_args_arr(char **args_arr);
char *_getenv(const char *name);
void print_environ(char **environ);
int builtin_cmd_handler(char **args_arr, int status, char *line);

#endif
