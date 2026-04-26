#include "shell.h"

/**
 * builtin_cmd_handler - handles execution of built in shell commands
 * @args_arr: array of arguments from user input
 * @status: exit status of last executed command
 * @line: raw input line from user
 *
 * Return: returns 1 if input is built in command, else 0
 */

int builtin_cmd_handler(char **args_arr, int status, char *line)
{
	int exit_status = status;

	if (strcmp(args_arr[0], "exit") == 0)
	{
		if (args_arr[1] != NULL)
		{
			if (!is_num(args_arr[1]))
			{
				fprintf(stderr, "%s: exit: %s: numeric argument required\n",
					program_name, args_arr[1]);
				exit_status = 2;
			}
			else
				exit_status = _atoi(args_arr[1]);
		}

		free_args_arr(args_arr);
		free(line);
		exit(exit_status);
	}

	if (strcmp(args_arr[0], "env") == 0)
	{
		print_environ(environ);
		free_args_arr(args_arr);
		return (1);
	}

	return (0);
}
