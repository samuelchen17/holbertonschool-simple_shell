#include "shell.h"

/**
 * fork_and_execve - clone current process and execute command in child
 * @args_arr: argument array created from tokenization
 * @cmd_path: full path to command
 * @status: exit status of last executed command
 */
void fork_and_execve(char **args_arr, char *cmd_path, int *status)
{
	pid_t pid;
	int wstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free(cmd_path);
		free_args_arr(args_arr);
		exit(1);
	}

	if (pid == 0)
	{
		execve(cmd_path, args_arr, environ);
		perror("execve failed");
		free(cmd_path);
		free_args_arr(args_arr);
		exit(1);
	}
	else
	{
		wait(&wstatus);

		if (WIFEXITED(wstatus))
			*status = WEXITSTATUS(wstatus);

		free(cmd_path);
		free_args_arr(args_arr);
	}
}

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
 * shell_program - simple shell
 * @program_name: shell program name
 */

void shell_program(char *program_name)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t input;
	char **args_arr;
	char *cmd_path;
	int line_num = 0;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		input = getline(&line, &n, stdin);
		if (input == -1)
			break;

		line_num++;
		line[strcspn(line, "\n")] = '\0';

		args_arr = get_tokens(line);
		if (args_arr == NULL || args_arr[0] == NULL)
		{
			free_args_arr(args_arr);
			continue;
		}

		if (builtin_cmd_handler(args_arr, status, line))
			continue;

		if (args_arr[0] == NULL)
		{
			free_args_arr(args_arr);
			continue;
		}

		cmd_path = handle_path(args_arr[0]);

		if (!cmd_path)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				program_name, line_num, args_arr[0]);
			status = 127;
			free_args_arr(args_arr);
			continue;
		}

		fork_and_execve(args_arr, cmd_path, &status);
	}

	free(line);
	exit(status);
}

/**
 * main - entry point for simple shell program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	(void)argc;
	shell_program(argv[0]);
	return (0);
}

