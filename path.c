#include "shell.h"

/* rebuild new env to add value */
int new_env_helper(const char *name, const char *value)
{
int size = 0, i = 0;
char *new_env_var;
char **new_env;

/* get size of environ for malloc*/
while(environ[size])
size++;

new_env = malloc(sizeof(char *) * (size + 2));
if (!new_env)
return -1;

/* copy old env to new */
for (i = 0; i < size; i++)
{
new_env[i] = environ[i];
}

new_env_var = malloc(strlen(name) + strlen(value) + 2);
if (!new_env_var)
{
free(new_env);
return -1;
}

sprintf(new_env_var, "%s=%s", name, value);
new_env[size] = new_env_var;
new_env[size + 1] = NULL;

environ = new_env;

return (0);
}

int _setenv(const char *name, const char *value, int overwrite)
{
int i = 0;
size_t n = strlen(name);
char *new_env_var;

/* loop through to find env that match */
while(environ[i])
{
if (strncmp(environ[i], name, n) == 0 && environ[i][n] == '=')
{
if (overwrite != 0)
{
/* +2 for '=' and '\0'*/
new_env_var = malloc(strlen(name) + strlen(value) + 2);
if (!new_env_var)
return -1;

/* build new str to be stored */
sprintf(new_env_var, "%s=%s", name, value);
free(environ[i]);
environ[i] = new_env_var;
}

return (0);
}
i++;
}

return (new_env_helper(name, value));
}

int _unsetenv(const char *name)
{
/*
deletes variable name from env
if no name match, env is unchanged
return 0 success, else -1
*/
(void)name;
return (0);
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
