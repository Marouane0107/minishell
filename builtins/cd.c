/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:28:43 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/21 17:08:15 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void    ft_setenv(t_env **env, char *s, char *path)
{
	t_env	*tmp;
	int		i;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
		{
			free(tmp->value);
			tmp->value = path;
			break;
		}
		tmp = tmp->next;
	}
}

void    change_path(t_env **env, char *path)
{
	char old_path[BUFFER_SIZE];

	getcwd(old_path, sizeof(BUFFER_SIZE));
	ft_setenv(env, "PWD", path);
	ft_setenv(env, "OLDPWD", old_path);
}

void    ft_cd(char *path, t_env **env)
{

	if (!path)
	{
		path = getenv("HOME");
		change_path(env, path);
	}
	else if (chdir(path) == -1 || access(path, F_OK) == -1)
		printf("cd: %s: No such file or directory\n", path);
	else if (access(path, (R_OK || W_OK) && X_OK) == -1)
		printf("cd: %s: Permission denied\n", path);
	else
		change_path(env, path);
		
}
