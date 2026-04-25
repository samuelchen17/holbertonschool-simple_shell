#include "shell.h"

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
 * print_environ - print all environment variables
 * @environ: environment variables
 */

void print_environ(char **environ)
{
int i = 0;

while(environ[i] != NULL)
{
printf("%s\n", environ[i]);
i++;
}
}