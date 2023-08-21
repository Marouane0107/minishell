# ifndef EXCUTION_H
#define EXCUTION_H

# include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#define BUFFER_SIZE 192400

typedef struct s_env
{
	char *value;
	char *name;
	struct s_env *next;
}       t_env;

// typedef struct s_cmd
// {
// 	char *cmd;
// 	char *value;
// 	char **argv;
// 	int ststus;
// }       t_cmd;

t_env	*get_environ(t_env *envi);
void	remove_node(t_env **env, char *name);
void	unset(char *argv[], t_env **env);
void	ft_env(t_env *env);
void	pwd(void);
void	ft_cd(char *path, t_env **env);
void    ft_exit(int status);
void	echo(int argc, char *argv[]);

# endif