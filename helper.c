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