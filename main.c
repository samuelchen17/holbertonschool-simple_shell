#include "shell.h"

/**
 * main - entry point for simple shell program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t input;
	int line_num = 0, status = 0;
	char **commands;
	int i;
	(void)argc;
	signal(SIGINT, signal_handler);
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		input = _getline(&line, &n, stdin);
		if (input == -1)
			break;

		line_num++;
		line[_strcspn(line, "\n")] = '\0';

		commands = split_cmds(line);
		if (commands == NULL)
			continue;

		i = 0;

		while (commands[i] != NULL)
		{
			if (run_cmd(commands[i], &status, line, argv[0], line_num)
				== BUILTIN_EXIT)
			{
				free_args_arr(commands);
				free(line);
				free_environment();
				exit(status);
			}
			i++;
		}

		free_args_arr(commands);
	}
	free(line);
	free_environment(); /* free copied environment, copy was made due to setenv*/
	exit(status);
}
