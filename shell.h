#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

extern char **environ;

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

/**
 * struct path_node - singly linked PATH directory list
 * @dir: directory path
 * @next: points to the next node
 */
typedef struct path_node
{
	char *dir;
	struct path_node *next;
} path_node_t;

/**
 * builtin_func_t - function pointer type for builtin command handlers
 * @args_arr: array of command arguments
 * @status: pointer to last command exit status
 * @line: raw input line from user
 * @program_name: name of the shell program
 * @line_num: current input line number
 */
typedef int (*builtin_func_t)(char **, int *, char *, char *, int);

/**
 * struct builtin_s - builtin command mapping
 * @name: builtin command name
 * @func: function that handles the builtin
 */
typedef struct builtin_s
{
	char *name;
	builtin_func_t func;
} builtin_t;

/* cmd.c */
int builtin_cmd_handler(char **args_arr, int *status, char *line, char *program_name, int line_num);
void signal_handler(int sig);
void run_cmd(char *cmd, int *status, char *line, char *program_name, int line_num);
int handle_cd_cmd(char **args_arr, int *status, char *line, char *program_name, int line_num);

/* env.c */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/* env_utils.c */
int valid_env_name(const char *name);
size_t count_env(void);
char *make_env_string(const char *name, const char *value);
int env_name_matches(const char *env, const char *name);
void print_environ(char **env);

/* env_mem_utils.c */
char ***owned_env_ref(void);
void free_environment(void);
void free_partial_env(char **env, size_t count);
int copy_environment(void);

/* exec.c */
void execute(char **args_arr, char *cmd_path, int *status);

/* path.c */
char *handle_path(char *cmd);
char *lookup_path(char *cmd);
char *build_path(char *dir, char *cmd);
void free_path_list(path_node_t *head);
path_node_t *add_node_end(path_node_t **head, char *dir);

/* tokens.c */
char **get_tokens(char *line);
void free_args_arr(char **args_arr);
int count_cmds(char *line);
char *copy_cmd(char *line, int start, int end);
char **split_cmds(char *line);

/* utils.c */
int file_exists(char *path);
int _is_delim(char c, const char *delim);
void *_realloc(void *ptr, size_t old_size, size_t new_size);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _atoi(char *s);
int is_num(char *s);

/* str_utils.c */
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *s, int c);
size_t _strcspn(const char *s, const char *reject);
char *_strtok(char *str, const char *delim);

/* handler.c */
int handle_exit_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num);
int handle_env_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num);
int handle_setenv_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num);
int handle_unsetenv_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num);
int handle_cd_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num);

#endif
