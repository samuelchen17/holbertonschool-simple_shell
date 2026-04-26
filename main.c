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
	char **args_arr;
	char *cmd_path;
	int line_num = 0;
	int status = 0;

	(void)argc;

	signal(SIGINT, signal_handler);

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

		if (builtin_cmd_handler(args_arr, status, line, argv[0], line_num))
			continue;

		cmd_path = handle_path(args_arr[0]);

		if (!cmd_path)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], line_num, args_arr[0]);
			status = 127;
			free_args_arr(args_arr);
			continue;
		}

		execute(args_arr, cmd_path, &status);	
	}

	free(line);
	exit(status);
}

