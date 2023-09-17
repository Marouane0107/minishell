/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:28:43 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/17 19:58:21 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

int	ft_export_check(char *name)
{
	t_env	*tmp;

	tmp = g_lobal.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_setenv(t_data *data, char *s, char *value)
{
	t_env	*tmp;

	if (!ft_strcmp(data->cmd[0], "export") && !value)
	{
		if (!ft_export_check(s))
			return (0);
	}
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
			free(tmp->value);
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	change_path(t_data *data, char *path)
{
	char	*old_path;
	char	*new_path;
	char	*pwd;

	old_path = NULL;
	pwd = NULL;
	new_path = NULL;
	old_path = getcwd(old_path, 0);
	if (!chdir(path))
	{
		g_lobal.pwd = getcwd(pwd, 0);
		ft_lstadd(&g_lobal.hold, lst_new(0, g_lobal.pwd, 0));
		new_path = getcwd(new_path, 0);
		ft_setenv(data, "PWD", new_path);
		ft_setenv(data, "OLDPWD", old_path);
	}
	ft_lstadd(&g_lobal.hold, lst_new(0, new_path, old_path));
}

void	cd_check(t_data *data, struct stat path_stat)
{
	if (S_ISDIR(path_stat.st_mode))
	{
		change_path(data, data->cmd[1]);
	}
	else if (S_ISREG(path_stat.st_mode))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
		g_lobal.ex = 1;
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": Unknown file type\n", 2);
		g_lobal.ex = 1;
	}
}

void	ft_cd(t_data *data)
{
	struct stat	path_stat;
	char		*path;

	path = data->cmd[1];
	if (data->cmd[1] && data->cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_lobal.ex = 1;
		return ;
	}
	if (!path || !ft_strcmp(path, "~"))
	{
		change_path(data, ft_getenv("HOME"));
	}
	else
	{
		if (stat(data->cmd[1], &path_stat) == 0)
		{
			cd_check(data, path_stat);
		}
		else
		{
			no_such_file_or_directory(data);
		}
	}
	free(path);
}
