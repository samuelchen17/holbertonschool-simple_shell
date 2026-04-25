#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
	size_t i, new_size;
	int c;
	char *new_buf;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	i = 0;
	while ((c = fgetc(stream)) != EOF)
	{
		if (i + 1 >= *n)
		{
			new_size = (*n) * 2;
			new_buf = realloc(*lineptr, new_size);
			if (new_buf == NULL)
				return (-1);
			*lineptr = new_buf;
			*n = new_size;
		}
		(*lineptr)[i] = (char)c;
		i++;
		if (c == '\n')
			break;
	}

	if (i == 0 && c == EOF)
		return (-1);

	(*lineptr)[i] = '\0';
	return ((ssize_t)i);
}


int main_two(void)
{
	char *line;
	char *cmd;
	char *argv[2];
	size_t len;
	ssize_t nread;
	pid_t pid;
	int status;

	line = NULL;
	len = 0;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		nread = _getline(&line, &len, stdin);

		if (nread == -1)
			break;

		cmd = _strtok(line, " \t\n");
		if (cmd == NULL)
			continue;

		argv[0] = cmd;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve");
				free(line);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
