#include "shell.h"

/**
 * _getenv - search and return matching env variable
 * @name: name of env variable to find
 *
 * Return: value of env variable
 */

char *_getenv(const char *name)
{
int i = 0;
size_t n = strlen(name);

while (environ[i] != NULL)
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

/**
 * handle_path - check if path exists
 * @cmd: command input from user
 *
 * Return: full path to executable, NULL if not found
 */

char *handle_path(char *cmd)
{
char *token;
char *path;
char *tmp;
size_t len = 0;
char *cmd_path = NULL;

struct stat file_info;

path = _getenv("PATH");
if (!path)
return (NULL);

tmp = strdup(path);
if (!tmp)
return (NULL);

token = strtok(tmp, ":");

while (token)
{
len = strlen(token) + strlen(cmd) + 2;

cmd_path = malloc(len);
if (!cmd_path)
{
free(tmp);
return (NULL);
}

/* build the path */
strcpy(cmd_path, token);
strcat(cmd_path, "/");
strcat(cmd_path, cmd);

/* check if path exists */
if (stat(cmd_path, &file_info) == 0)
{
free(tmp);
return (cmd_path);
}

free(cmd_path);
cmd_path = NULL;

token = strtok(NULL, ":");
}

free(tmp);
return (NULL);
}