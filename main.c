#include "shell.h"
extern char **environ;

int _setenv(const char *name, const char *value, int overwrite)
{
// adds variable name to env
// if name exists, overwrite the value if overwrite != 0
// on success, makes copies of the str, 
// return 0 success, else -1

int i = 0;
size_t n = strlen(name);
char *new_env_var;

/* loop through to find env that match */
while(environ[i])
{
if (strncmp(environ[i], name, n) == 0 && environ[i][n] == '=')
{
if (overwrite)
{
/* +2 for '=' and '\0'*/
new_env_var = malloc(strlen(name) + strlen(value) + 2);
if (!new_env_var)
return -1;

/* build new str to be stored */
sprintf(new_var, "%s=%s", name, value);
environ[i] = new_env_var;
}

return (0);
}
i++;
}

return (-1);
}

int _unsetenv(const char *name)
{
// deletes variable name from env
// if no name match, env is unchanged
// return 0 success, else -1
}

list_t *add_node_end(list_t **head, char *token)
{
list_t *ptr, *node;

/* check if token is valid */
if (!token)
return (NULL);

/* malloc memory for node */
node = malloc(sizeof(list_t));
if (!node)
return (NULL);

/* set next for node, cpy token and check for failure */
node->next = NULL;
node->dir_path = strdup(token);
if (!node->dir_path)
{
free(node);
return (NULL);
}

/* if no list, return node as head */
if (*head == NULL)
{
*head = node;
return (node);
}

ptr = *head;
while (ptr->next != NULL)
ptr = ptr->next;

ptr->next = node;

return (*head);
}

void print_environ(char **environ)
{
int i = 0;

while(environ[i] != NULL)
{
printf("%s\n", environ[i]);
i++;
}
}

char *_getenv(const char *name)
{
int i = 0;
size_t n = strlen(name);

while(environ[i] != NULL)
{
if (strncmp(environ[i], name, n) == 0 && environ[i][n] == '=')
{
/* needs to return value of env, ptr math */
return (environ[i] + n + 1);
}
i++;
}

return (NULL);
}

list_t *tokenise_env_paths(void)
{
char *token;
char *path;
char *tmp;
list_t *head = NULL;

path = _getenv("PATH");
if(!path)
return (NULL);

tmp = strdup(path);
if (!tmp)
return NULL;

token = strtok(tmp, ":");

while (token)
{
/* add to linked list */
add_node_end(&head, token);
token = strtok(NULL, ":");
}

free(tmp);
return (head);
}

/**
 * free_args_arr - free argument array created from tokenization
 * @args_arr: argument array created from tokenization
 */
void free_args_arr(char **args_arr)
{
int i = 0;

if (!args_arr)
return;

while (args_arr[i] != NULL)
{
free(args_arr[i]);
i++;
}
free(args_arr);
}

/**
 * fork_and_execve - clone current process and execute command in child
 * @args_arr: argument array created from tokenization
 */
void fork_and_execve(char **args_arr)
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("fork failed");
free_args_arr(args_arr);
exit(1);
}
/* on child creation success */
if (pid == 0)
{
/*
* for testing
* printf("token passed: [%s]\n", args_arr[0]);
*/
execve(args_arr[0], args_arr, NULL);
perror("execve failed");
free_args_arr(args_arr);
exit(1);
}
else
{
/* parent to wait for child process to exit */
wait(&status);
free_args_arr(args_arr);
}
}

/**
 * get_tokens - separate words from user input into tokens
 * @line: string of user input
 *
 * Return: array of arguments
 */

char **get_tokens(char *line)
{
char **args_arr;
/* tmp needed as strtok modifies the str */
char *token, *tmp = strdup(line);
int i = 0, count = 0;

/* first iteration count tokens for malloc size*/
token = strtok(tmp, " ");
while (token != NULL)
{
count++;
/* strtok stores /0 when it stops, by using NULL it will continue to next */
token = strtok(NULL, " ");
}
free(tmp);

/* allocate exact memory */
args_arr = malloc((count + 1) * sizeof(char *));

/* loop to store tokens */
token = strtok(line, " ");
while (token != NULL)
{
args_arr[i] = strdup(token);
token = strtok(NULL, " ");
i++;
}
args_arr[i] = NULL;

/*
* for testing
i = 0;
while (args_arr[i] != NULL)
{
printf("args arr[%i]: %s\n", i, args_arr[i]);
i++;
}
*/

return (args_arr);
}

/**
 * get_prompt - get user input
 */

void get_prompt(void)
{
char *line = NULL;
size_t n = 0;
ssize_t input;
char **args_arr;

while (1)
{
if (isatty(STDIN_FILENO))
{
printf("$ ");
}

input = getline(&line, &n, stdin);

/* break loop upon EOF or error*/
if (input == -1)
{
break;
}

/* remove \n for tokenization */
line[strcspn(line, "\n")] = '\0';

args_arr = get_tokens(line);

/* block invalid command before execve */
if (args_arr[0] == NULL)
{
free_args_arr(args_arr);
continue;
}

fork_and_execve(args_arr);
}

free(line);
}

/**
 * main - entry to program
 * Return: int
 */

int main(int argc, char **argv, char **envp)
{
(void)argc;
(void)argv;
(void)envp;

tokenise_env_paths();


/* for testing */
/*
list_t *head = tokenise_env_paths();
while (head)
{
printf("%s\n", head->dir_path);
head = head->next;
}
*/
return (0);
}
