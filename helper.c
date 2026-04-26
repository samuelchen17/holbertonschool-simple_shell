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

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * is_num - check if string is a number
 * @s: pointer to string
 *
 * Return: 1 if true and 0 if false
 */
int is_num(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}

	return (1);
}

/**
 * _atoi - converts string to integer
 * @s: pointer to string
 *
 * Return: converted integer
 */
int _atoi(char *s)
{
	int i = 0;
	int minus_counter = 0;
	int num = 0;
	int sign = 1;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			minus_counter++;

		if (s[i] >= '0' && s[i] <= '9')
			break;

		i++;
	}

	/* if no digits, return 0 */
	if (s[i] == '\0')
		return (0);

	/* determine the sign */
	if (minus_counter % 2 == 1)
		sign = -1;

	/* combine number */
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (sign == 1)
			num = num * 10 + (s[i] - '0');
		else
			num = num * 10 - (s[i] - '0');

		i++;
	}

	return (num);
}
