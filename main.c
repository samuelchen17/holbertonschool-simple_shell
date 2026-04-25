#include "shell.h"

/**
 * free_args_arr - Free argument array created from tokenization
 * @args_arr: Argument array created from tokenization
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
 * fork_and_execve - Clone current process and execute command in child
 * @args_arr: Argument array created from tokenization
 */
void fork_and_execve(char **args_arr)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free_args_arr(args_arr);
		exit(1);
	}

	if (pid == 0)
	{
		execve(args_arr[0], args_arr, NULL);
		perror("execve failed");
		free_args_arr(args_arr);
		exit(1);
	}

	wait(&status);
	free_args_arr(args_arr);
}

/**
 * get_tokens - Separate words from user input into tokens
 * @line: String of user input
 *
 * Return: Array of arguments
 */
char **get_tokens(char *line)
{
	char **args_arr;
	char *token, *tmp = strdup(line);
	int i = 0, count = 0;

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
		token = strtok(NULL, " ");
		i++;
	}
	args_arr[i] = NULL;

	return (args_arr);
}

/**
 * get_prompt - Get user input
 */
void get_prompt(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t input;
	char **args_arr;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		input = getline(&line, &n, stdin);
		if (input == -1)
			break;

		line[strcspn(line, "\n")] = '\0';
		args_arr = get_tokens(line);

		if (args_arr == NULL || args_arr[0] == NULL)
		{
			free_args_arr(args_arr);
			continue;
		}

		fork_and_execve(args_arr);
	}

	free(line);
}

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	get_prompt();

	return (0);
}

