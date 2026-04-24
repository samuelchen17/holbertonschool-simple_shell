#include "shell.h"

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

/* allocate exact mem */
args_arr = malloc((count + 1) * sizeof(char*));

/* loop to store tokens */
token = strtok(line, " ");
while (token != NULL)
{
args_arr[i] = strdup(token);
token = strtok(NULL, " ");
i++;
}
args_arr[i] = NULL;

i = 0;
while (args_arr[i] != NULL)
{
printf("args arr[%i]: %s\n", i, args_arr[i]);
i++;
}

return (args_arr);
}

/**
 * get_prompt - get user input
 */

void get_prompt(void)
{
char *line = NULL;
size_t n = 0;
ssize_t input;
char **args_arr;

while (1)
{
printf("$ ");
input = getline(&line, &n, stdin);

/* break loop upon EOF or error*/
if (input == -1)
{
printf("\n");
break;
}

args_arr = get_tokens(line);
}

free(line);
}

/**
 * main - 
 */

int main(void)
{
get_prompt();

return (0);
}
