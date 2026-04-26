#include "shell.h"

/**
 * execute - clone current process and execute command in child
 * @args_arr: argument array created from tokenization
 * @cmd_path: full path to command
 * @status: exit status of last executed command
 */
void execute(char **args_arr, char *cmd_path, int *status)
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
