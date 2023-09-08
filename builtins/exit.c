/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:16 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/07 16:56:18 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_exit(t_data *data)
{
	printf("hdf\n");
	if (data->cmd[1] && !data->cmd[2])
		exit(ft_atoi(data->cmd[1]));
	if (data->cmd[1] && data->cmd[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return;
	}
	exit(g_lobal.ex);
}
