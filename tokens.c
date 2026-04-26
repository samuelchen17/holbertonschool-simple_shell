#include "shell.h"

/**
 * get_tokens - separate words from user input into tokens
 * @line: string of user input
 *
 * Return: array of arguments
 */
char **get_tokens(char *line)
{
	char **args_arr;
	char *token, *tmp;
	int i = 0, count = 0;

	tmp = strdup(line);
	if (tmp == NULL)
		return (NULL);

	token = strtok(tmp, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}
	free(tmp);

	args_arr = malloc((count + 1) * sizeof(char *));
	if (args_arr == NULL)
		return (NULL);

	token = strtok(line, " ");
	while (token != NULL)
	{
		args_arr[i] = strdup(token);
		if (args_arr[i] == NULL)
		{
			free_args_arr(args_arr);
			return (NULL);
		}
		token = strtok(NULL, " ");
		i++;
	}
	args_arr[i] = NULL;

	return (args_arr);
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
