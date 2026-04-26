#include "shell.h"

int file_exists(char *path)
{
	struct stat st;

	return (stat(path, &st) == 0);
}

int _is_delim(char c, const char *delim)
{
	int i;

	i = 0;
	while (delim[i] != '\0')
	{
		if (c == delim[i])
			return (1);
		i++;
	}
	return (0);
}

char *_strtok(char *str, const char *delim)
{
	static char *next;
	char *token_start;

	if (str != NULL)
		next = str;

	if (next == NULL || delim == NULL)
		return (NULL);

	while (*next != '\0' && _is_delim(*next, delim))
		next++;

	if (*next == '\0')
	{
		next = NULL;
		return (NULL);
	}

	token_start = next;

	while (*next != '\0' && !_is_delim(*next, delim))
		next++;

	if (*next == '\0')
	{
		next = NULL;
		return (token_start);
	}

	*next = '\0';
	next++;
	return (token_start);
}

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i = 0;
	size_t new_size;
	ssize_t bytes;
	char c;
	char *new_buf;

	(void)stream;

	if (lineptr == NULL || n == NULL)
		return (-1);

	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(sizeof(char) * (*n));
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		bytes = read(STDIN_FILENO, &c, 1);

		if (bytes == -1)
			return (-1);

		if (bytes == 0)
			break;

		if (i + 1 >= *n)
		{
			new_size = (*n) * 2;
			new_buf = realloc(*lineptr, new_size);
			if (new_buf == NULL)
				return (-1);

			*lineptr = new_buf;
			*n = new_size;
		}

		(*lineptr)[i] = c;
		i++;

		if (c == '\n')
			break;
	}

	if (i == 0)
		return (-1);

	(*lineptr)[i] = '\0';

	return ((ssize_t)i);
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
