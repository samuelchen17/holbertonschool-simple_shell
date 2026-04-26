#include "shell.h"

/**
 * handle_exit_cmd - handles exit builtin
 * @args_arr: command arguments
 * @status: current shell status
 * @line: raw input line
 * @program_name: shell program name
 * @line_num: current line number
 *
 * Return: 1 because command was handled
 */
int handle_exit_cmd(char **args_arr, int *status, char *line, char *program_name, int line_num)
{
	int exit_status = *status;

	if (args_arr[1] != NULL)
	{
		if (!is_num(args_arr[1]))
		{
			fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
				program_name, line_num, args_arr[1]);
			exit_status = 2;
		}
		else
			exit_status = _atoi(args_arr[1]);
	}

	free_args_arr(args_arr);
	free(line);
	free_environment(); /* free copied environment, copy was made due to setenv*/
	exit(exit_status);
}

/**
 * handle_env_cmd - handles env builtin
 * @args_arr: command arguments
 * @status: current shell status
 * @line: raw input line
 * @program_name: shell program name
 * @line_num: current line number
 *
 * Return: 1 because command was handled
 */
int handle_env_cmd(char **args_arr, int *status, char *line, char *program_name, int line_num)
{
	(void)line;
	(void)program_name;
	(void)line_num;

	print_environ(environ);
	*status = 0;
	free_args_arr(args_arr);

	return (1);
}

/**
 * handle_setenv_cmd - handles setenv builtin
 * @args_arr: command arguments
 * @status: current shell status
 * @line: raw input line
 * @program_name: shell program name
 * @line_num: current line number
 *
 * Return: 1 because command was handled
 */
int handle_setenv_cmd(char **args_arr, int *status, char *line, char *program_name, int line_num)
{
	(void)line;

	if (args_arr[1] == NULL || args_arr[2] == NULL)
	{
		fprintf(stderr, "%s: %d: setenv: Usage: setenv VARIABLE VALUE\n", program_name, line_num);
		*status = 2;
		free_args_arr(args_arr);
		return (1);
	}

	if (_setenv(args_arr[1], args_arr[2], 1) == -1)
	{
		fprintf(stderr, "%s: %d: setenv: failed\n", program_name, line_num);
		*status = 2;
	}
	else
		*status = 0;

	free_args_arr(args_arr);
	return (1);
}

/**
 * handle_unsetenv_cmd - handles unsetenv builtin
 * @args_arr: command arguments
 * @status: current shell status
 * @line: raw input line
 * @program_name: shell program name
 * @line_num: current line number
 *
 * Return: 1 because command was handled
 */
int handle_unsetenv_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num)
{
	(void)line;

	if (args_arr[1] == NULL)
	{
		fprintf(stderr, "%s: %d: unsetenv: Usage: unsetenv VARIABLE\n", program_name, line_num);
		*status = 2;
		free_args_arr(args_arr);
		return (1);
	}

	if (_unsetenv(args_arr[1]) == -1)
	{
		fprintf(stderr, "%s: %d: unsetenv: failed\n", program_name, line_num);
		*status = 2;
	}
	else
		*status = 0;

	free_args_arr(args_arr);
	return (1);
}

int handle_cd_cmd(char **args_arr, int *status, char *line, char *program_name, int line_num)
{
    char *path;
	(void)status;
	(void)line;
	(void)program_name;
	(void)line_num;

    if (strcmp(args_arr[0], "cd") != 0)
        return 0;

    if (args_arr[1] == NULL)
    {
        path = _getenv("HOME");
    }
    else if (strcmp(args_arr[1], "-") == 0)
    {
        path = _getenv("OLDPWD");
    }
    else
    {
        path = args_arr[1];
    }

    if (chdir(path) != 0)
    {
        perror("cd");
    }

    return 1;
}

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
int builtin_cmd_handler(char **args_arr, int *status, char *line, char *program_name, int line_num)
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
 * Return: void
 */
void run_cmd(char *cmd, int *status, char *line,
	char *program_name, int line_num)
{
	char **args_arr;
	char *cmd_path;

	args_arr = get_tokens(cmd);
	if (args_arr == NULL || args_arr[0] == NULL)
	{
		free_args_arr(args_arr);
		return;
	}

	if (builtin_cmd_handler(args_arr, status, line, program_name, line_num))
		return;

	cmd_path = handle_path(args_arr[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_num, args_arr[0]);
		*status = 127;
		free_args_arr(args_arr);
		return;
	}

	execute(args_arr, cmd_path, status);
}
