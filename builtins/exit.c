/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:16 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/16 03:36:58 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void	No_such_file_or_directory(t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_lobal.ex = 1;
}

void	cmd_not_found(t_data *data, int i)
{
	ft_putstr_fd(data->cmd[i], 2);
	ft_putstr_fd(": command not found\n", 2);
	g_lobal.ex = 127;
}

void	numiric_arg(t_data *data)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(data->cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(2);
}

void	ft_exit(t_data *data)
{
	if (data->cmd[1] && !data->cmd[2])
	{
		if (ft_isdigit(data->cmd[1][0]) == 1)
			exit(ft_atoi(data->cmd[1]));
		else
			numiric_arg(data);
	}
	if (data->cmd[1] && data->cmd[2])
	{
		if (ft_isdigit(data->cmd[1][0]) != 1)
			numiric_arg(data);
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return ;
	}
	exit(g_lobal.ex);
}
