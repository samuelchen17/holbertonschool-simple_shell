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

	tmp = _strdup(line);
	if (tmp == NULL)
		return (NULL);

	token = _strtok(tmp, " ");
	while (token != NULL)
	{
		count++;
		token = _strtok(NULL, " ");
	}
	free(tmp);

	args_arr = malloc((count + 1) * sizeof(char *));
	if (args_arr == NULL)
		return (NULL);

	token = _strtok(line, " ");
	while (token != NULL)
	{
		args_arr[i] = _strdup(token);
		if (args_arr[i] == NULL)
		{
			free_args_arr(args_arr);
			return (NULL);
		}
		token = _strtok(NULL, " ");
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

/**
 * count_cmds - counts commands separated by ;
 * @line: input line
 *
 * Return: number of command segments
 */
int count_cmds(char *line)
{
	int i = 0;
	int count = 1;

	if (line == NULL || line[0] == '\0')
		return (0);

	while (line[i] != '\0')
	{
		if (line[i] == ';')
			count++;
		i++;
	}

	return (count);
}

/**
 * copy_cmd - copies part of line into new string
 * @line: input line
 * @start: start index
 * @end: end index
 *
 * Return: malloc'd command string
 */
char *copy_cmd(char *line, int start, int end)
{
	char *cmd;
	int i = 0;
	int len;

	len = end - start;
	cmd = malloc(sizeof(char) * (len + 1));
	if (cmd == NULL)
		return (NULL);

	while (start < end)
	{
		cmd[i] = line[start];
		i++;
		start++;
	}

	cmd[i] = '\0';
	return (cmd);
}

/**
 * split_cmds - splits input line by ;
 * @line: input line
 *
 * Return: array of command strings
 */
char **split_cmds(char *line)
{
	char **commands;
	int i = 0, j = 0, start = 0;
	int count;

	count = count_cmds(line);
	if (count == 0)
		return (NULL);

	commands = malloc(sizeof(char *) * (count + 1));
	if (commands == NULL)
		return (NULL);

	while (line[i] != '\0')
	{
		if (line[i] == ';')
		{
			commands[j] = copy_cmd(line, start, i);
			if (commands[j] == NULL)
			{
				free_args_arr(commands);
				return (NULL);
			}
			j++;
			start = i + 1;
		}
		i++;
	}

	commands[j] = copy_cmd(line, start, i);
	if (commands[j] == NULL)
	{
		free_args_arr(commands);
		return (NULL);
	}
	j++;

	commands[j] = NULL;
	return (commands);
}
