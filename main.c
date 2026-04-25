#include "shell.h"

/**
 * fork_and_execve - clone current process and execute command in child
 * @args_arr: argument array created from tokenization
 */
void fork_and_execve(char **args_arr, char *cmd_path)
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
/* on child creation success */
if (pid == 0)
{
/*
* for testing
* printf("token passed: [%s]\n", args_arr[0]);
*/
execve(cmd_path, args_arr, environ);
perror("execve failed");
free_args_arr(args_arr);
exit(1);
}
else
{
/* parent to wait for child process to exit */
wait(&status);
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
/* tmp needed as strtok modifies the str */
char *token, *tmp = strdup(line);
int i = 0, count = 0;

/* first iteration count tokens for malloc size*/
token = strtok(tmp, " ");
while (token != NULL)
{
count++;
/* strtok stores /0 when it stops, by using NULL it will continue to next */
token = strtok(NULL, " ");
}
free(tmp);

/* allocate exact memory */
args_arr = malloc((count + 1) * sizeof(char *));

/* loop to store tokens */
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
 * get_prompt - get user input
 */

void get_prompt(char *program_name)
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
{
printf("$ ");
}

input = getline(&line, &n, stdin);

/* break loop upon EOF or error*/
if (input == -1)
{
break;
}

line_num++;

/* remove \n for tokenization */
line[strcspn(line, "\n")] = '\0';

args_arr = get_tokens(line);

/* block invalid command before execve */
if (args_arr[0] == NULL)
{
free_args_arr(args_arr);
continue;
}

/* HANDLE PATH LOGIC HERE */
cmd_path = handle_path(args_arr[0]);

if (!cmd_path)
{
fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_num, args_arr[0]);
status = 127;
free_args_arr(args_arr);
continue;
}

fork_and_execve(args_arr, cmd_path);
}

free(line);
exit(status);
}

/**
 * main - entry point for simple shell program
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
(void)argc;
get_prompt(argv[0]);
return (0);
}
