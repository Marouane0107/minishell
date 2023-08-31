#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include "minishell.h"
int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *cmd[] = {"echo", "hello", "world", NULL};
    execve("/usr/bin/echo", cmd, NULL);
}