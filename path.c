#include "shell.h"

/**
 * build_path - build full path name for command
 * @token: directory path
 * @cmd: command input from user
 *
 * Return: full path to executable, NULL if not found
 */
char *build_path(char *token, char *cmd)
{
char *path;
size_t len;

len = strlen(token) + strlen(cmd) + 2;

path = malloc(len);
if (!path)
{
return (NULL);
}

/* build the path */
strcpy(path, token);
strcat(path, "/");
strcat(path, cmd);

return (path);
}

/**
 * lookup_path - check if path exists
 * @cmd: command input from user
 *
 * Return: full path to executable, NULL if not found
 */

char *lookup_path(char *cmd)
{
char *token;
char *path;
char *tmp;
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
cmd_path = build_path(token, cmd);
if (!cmd_path)
{
free(tmp);
return (NULL);
}

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

/**
 * handle_path - check if path exists
 * @cmd: command input from user
 *
 * Return: full path to executable, NULL if not found
 */

char *handle_path(char *cmd)
{
if (strchr(cmd, '/'))
{
if (access(cmd, X_OK) == 0)
return strdup(cmd);

return (NULL);
}

return (lookup_path(cmd));
}