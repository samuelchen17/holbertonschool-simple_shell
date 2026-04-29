#include "shell.h"

/**
 * handle_exit_cmd - handles exit builtin
 * @args_arr: command arguments
 * @status: current shell status
 * @line: raw input line
 * @program_name: shell program name
 * @line_num: current line number
 *
 * Return: 2 because shell should exit
 */
int handle_exit_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num)
{
	int exit_status = *status;
	(void)line;

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

	*status = exit_status;
	free_args_arr(args_arr);
	return (2);
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
int handle_env_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num)
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
int handle_setenv_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num)
{
	(void)line;

	if (args_arr[1] == NULL || args_arr[2] == NULL)
	{
		fprintf(stderr, "%s: %d: setenv: Usage: setenv VARIABLE VALUE\n",
			program_name, line_num);
		*status = 2;
		free_args_arr(args_arr);
		return (1);
	}

	if (_setenv(args_arr[1], args_arr[2], 1) == -1)
	{
		fprintf(stderr, "%s: %d: setenv: failed\n",
			program_name, line_num);
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
		fprintf(stderr, "%s: %d: unsetenv: Usage: unsetenv VARIABLE\n",
			program_name, line_num);
		*status = 2;
		free_args_arr(args_arr);
		return (1);
	}

	if (_unsetenv(args_arr[1]) == -1)
	{
		fprintf(stderr, "%s: %d: unsetenv: failed\n",
			program_name, line_num);
		*status = 2;
	}
	else
		*status = 0;

	free_args_arr(args_arr);
	return (1);
}

/**
 * handle_cd_cmd - handles cd builtin
 * @args_arr: command arguments
 * @status: current shell status
 * @line: raw input line
 * @program_name: shell program name
 * @line_num: current line number
 *
 * Return: 1 because command was handled, 0 if not cd
 */
int handle_cd_cmd(char **args_arr, int *status, char *line,
	char *program_name, int line_num)
{
	char *path;
	char oldpwd[CD_BUF_SIZE];
	int print_pwd;

	(void)line;

	if (strcmp(args_arr[0], "cd") != 0)
		return (0);

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		oldpwd[0] = '\0';

	path = get_cd_path(args_arr, &print_pwd);

	if (path == NULL || path[0] == '\0' || chdir(path) != 0)
	{
		fprintf(stderr, "%s: %d: cd: can't cd to %s\n",
			program_name, line_num, path ? path : "");
		*status = 2;
		free_args_arr(args_arr);
		return (1);
	}

	update_pwd_vars(oldpwd, print_pwd);
	*status = 0;
	free_args_arr(args_arr);
	return (1);
}
