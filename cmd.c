#include "shell.h"

/**
 * builtin_cmd_handler - dispatches builtin shell commands
 * @args_arr: array of arguments from user input
 * @status: exit status of last command
 * @line: raw input line from user
 * @program_name: shell program name
 * @line_num: current input line number
 *
 * Return: 1 if command is builtin, otherwise 0
 */
int builtin_cmd_handler(char **args_arr, int *status, char *line,
	char *program_name, int line_num)
{
	builtin_t builtins[] = {
		{"exit", handle_exit_cmd},
		{"env", handle_env_cmd},
		{"setenv", handle_setenv_cmd},
		{"unsetenv", handle_unsetenv_cmd},
		{"cd", handle_cd_cmd},
		{NULL, NULL}
	};
	int i = 0;

	if (args_arr == NULL || args_arr[0] == NULL)
		return (0);

	while (builtins[i].name != NULL)
	{
		if (_strcmp(args_arr[0], builtins[i].name) == 0)
			return (builtins[i].func(args_arr, status, line, program_name, line_num));
		i++;
	}

	return (0);
}

/**
 * signal_handler - handles SIGINT signal
 * @sig: signal number received
 *
 * Return: void
 */
void signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * run_cmd - runs one parsed command string
 * @cmd: command string
 * @status: shell status
 * @line: original input line
 * @program_name: shell program name
 * @line_num: current line number
 *
 * Return: int
 */
int run_cmd(char *cmd, int *status, char *line,
	char *program_name, int line_num)
{
	char **args_arr;
	char *cmd_path;
	int builtin_status;

	args_arr = get_tokens(cmd);
	if (args_arr == NULL || args_arr[0] == NULL)
	{
		free_args_arr(args_arr);
		return (BUILTIN_HANDLED);
	}

	builtin_status = builtin_cmd_handler(args_arr, status, line,
		program_name, line_num);
	if (builtin_status != BUILTIN_NOT_FOUND)
		return (builtin_status);

	cmd_path = handle_path(args_arr[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			program_name, line_num, args_arr[0]);
		*status = 127;
		free_args_arr(args_arr);
		return (BUILTIN_HANDLED);
	}

	execute(args_arr, cmd_path, status);
	return (BUILTIN_HANDLED);
}
