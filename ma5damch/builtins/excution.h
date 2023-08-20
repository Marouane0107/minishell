# ifndef EXCUTION_H
#define EXCUTION_H

# include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

typedef struct s_env
{
    char *value;
    char *name;
    struct s_env *next;
}        t_env;

t_env	*get_environ(t_env *envi);
void    remove_node(t_env **env, char *name);
void    unset(char *argv[], t_env **env);
void    env(t_env *env);
void    pwd(void);
void    cd(char *path);
void    echo(int argc, char *argv[]);

# endif