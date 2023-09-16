/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:16 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/15 22:31:36 by maouzal          ###   ########.fr       */
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

void	ft_exit(t_data *data)
{
	if (data->cmd[1] && !data->cmd[2])
	{
		if (ft_isdigit(data->cmd[1][0]) == 1)
			exit(ft_atoi(data->cmd[1]));
		else
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 1);
			ft_putstr_fd(data->cmd[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			exit(2);
		}
	}
	if (data->cmd[1] && data->cmd[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return ;
	}
	exit(g_lobal.ex);
}
