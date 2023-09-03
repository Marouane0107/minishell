/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:28:43 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/03 20:25:57 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

char	*ft_getenv(char *s)
{
	t_env	*tmp;

	tmp = g_lobal.env;
	while (tmp)
	{
		if (tmp && !ft_strcmp(tmp->name, s))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_setenv(t_data *data, char *s, char *value)
{
	t_env	*tmp;

	tmp = g_lobal.env;
	while (tmp && value)
	{
		if (!ft_strcmp(tmp->name, s))
		{
			if (data->f == 1)
			{
				tmp->value = ft_strjoin(tmp->value, value);
				return (0);
			}
			tmp->value = NULL;
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void    change_path(t_data *data, char *path)
{
	char	old_path[BUFFER_SIZE];
	char	new_path[BUFFER_SIZE];

	getcwd(old_path, sizeof(old_path));
	// printf("p:%s\n", path);
	// printf("%s\n", old_path);
	if (!chdir(path))
	{
		getcwd(new_path, sizeof(new_path));
		// printf("%s\n", new_path);
		// if (!ft_strcmp(new_path, path))
		// 	{
		// 		ft_setenv(data, "PWD", new_path);
		// 		ft_setenv(data, "OLDPWD", old_path);
		// 	}
		// else
		//{
			ft_setenv(data, "PWD", new_path);
			ft_setenv(data, "OLDPWD", old_path);
		//}
	}
}

void    ft_cd(t_data *data)
{

	if (!(data->cmd[1]) || !(ft_strcmp(data->cmd[1], "~")))
		change_path(data, ft_getenv("HOME"));
	else if (!ft_strcmp(data->cmd[1], "-"))
	{
		change_path(data, ft_getenv("OLDPWD"));
		printf("%s\n", ft_getenv("PWD"));
	}
	else if (access(data->cmd[1], X_OK) == -1 || access(data->cmd[1], F_OK) == -1)
		printf("cd: %s: No such file or directory\n", data->cmd[1]);
	else if (access(data->cmd[1], F_OK) == 0 && access(data->cmd[1], X_OK) == -1)
		printf("cd: %s: Not a directory\n", data->cmd[1]);
	else if (access(data->cmd[1], F_OK) == 0 && access(data->cmd[1], X_OK) == 0)
		change_path(data, data->cmd[1]);
	else
		printf("cd: %s: No such file or directory\n", data->cmd[1]);
		
}
