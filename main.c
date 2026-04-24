#include "shell.h"


void get_prompt(void)
{
char *line = NULL;
size_t n = 0;
ssize_t input;

while (1)
{
printf("$ ");
input = getline(&line, &n, stdin);

if (input == -1)
{
printf("\n");
break;
}
else
printf("%s", line);

}
free (line);
}

int main(void)
{
get_prompt();

return (0);
}
