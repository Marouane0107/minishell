/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:09 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/17 04:14:50 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

int	ft_echo_norm(t_data *data, int i, int j, int k)
{
	if (data->cmd[1][0] == '-' && data->cmd[1][1] == 'n')
	{
		g_lobal.new_line = 1;
		while (data->cmd[i] && g_lobal.new_line == 1 && data->cmd[i][0] == '-'
			&& data->cmd[i][1] == 'n')
		{
			while (data->cmd[i][j] == 'n')
				j++;
			if (data->cmd[i][j] == '\0')
			{
				g_lobal.new_line = 1;
				k++;
			}
			else
				g_lobal.new_line = 0;
			i++;
			j = 1;
		}
		if (g_lobal.new_line == 0)
			i--;
		if (k > 0)
			g_lobal.new_line = 1;
	}
	return (i);
}

void	ft_echo(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 1;
	k = 0;
	g_lobal.new_line = 0;
	if (!data->cmd[1])
	{
		printf("\n");
		return ;
	}
	i = ft_echo_norm(data, i, j, k);
	while (data->cmd && data->cmd[i])
	{
		printf("%s", data->cmd[i]);
		i++;
		if (data->cmd[i])
			printf(" ");
	}
	if (g_lobal.new_line == 0)
		printf("\n");
}
