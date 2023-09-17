/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:40:02 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/17 03:47:16 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd(t_data *data)
{
	t_data	*tmp;

	tmp = data;
	while (tmp && tmp->next)
	{
		if (!tmp->cmd)
		{
			tmp->cmd = tmp->next->cmd;
		}
		else
			return ;
	}
}

void	check_cmd_path(t_data *data)
{
	int			i;
	extern char	**environ;

	i = 0;
	if (!data->cmd)
		return ;
	while (data->cmd[i])
	{
		if (data->cmd[i][0] == '/' || data->cmd[i][0] == '.')
		{
			if (access(data->cmd[i], X_OK) == -1)
			{
				cmd_not_found(data, i);
				g_lobal.ex = 127;
				exit(127);
			}
			else if (execve(data->cmd[i], data->cmd, environ) == -1)
			{
				cmd_not_found(data, i);
				exit(127);
			}
		}
		i++;
	}
}

void	exution(t_data *data, char **path_part, int i)
{
	char		*cmd_path;
	char		*path_cmd;
	extern char	**environ;

	if (!*data->cmd[0])
		return (ft_putstr_fd("'': command not found\n", 2), g_lobal.ex = 127,
			exit(127));
	while (path_part && path_part[i])
	{
		cmd_path = ft_strjoin(path_part[i], "/");
		path_cmd = ft_strjoin(cmd_path, data->cmd[0]);
		if (access(path_cmd, X_OK) == -1)
		{
			if (path_cmd)
				free(path_cmd);
		}
		else if (execve(path_cmd, data->cmd, environ) == -1)
		{
			cmd_not_found(data, 0);
			exit(127);
		}
		i++;
	}
}

void	exec_cmd(t_data *data)
{
	int		i;
	char	*path;
	char	**path_part;

	i = 0;
	if (!data->cmd || !*data->cmd)
		return ;
	if (data->in == -3 || data->out == -3)
		return ;
	path = ft_getenv("PATH");
	if (data->cmd[i][0] == '/' || data->cmd[i][0] == '.')
		check_cmd_path(data);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		cmd_not_found(data, 0);
		exit(127);
	}
	path_part = ft_split(path, ':');
	get_cmd(data);
	exution(data, path_part, i);
	cmd_not_found(data, i);
	exit(127);
}
