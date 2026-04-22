#include "shell.h"

void print_pid(void)
{
pid_t my_pid;

my_pid = getpid();
printf("%u\n", my_pid);
}

void print_ppid(void)
{
pid_t my_ppid;

my_ppid = getppid();
printf("%u\n", my_ppid);
}



