/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:09 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/04 22:32:26 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_echo(t_data *data)
{
	int i;
	int f;
	int j;

	i = 1;
	j = 1;
	f = 1;
	if(!data->cmd[1])
	{
		printf("\n");
		return;
	}
	if (data->cmd[1][0] == '-' && data->cmd[1][1] =='n')
	{
		while (data->cmd[i][0] == '-' && data->cmd[i][1] == 'n' && f == 1)
		{
			f = 0;
			while (data->cmd[i][j] == 'n')
				j++;
			if (data->cmd[i][j] == '\0')
				f = 1;
			i++;
			j = 1;
		}
		if (f == 0)
			i--;
		f = 0;
	}
	while (data->cmd && data->cmd[i])
	{
		printf("%s",data->cmd[i]);
		i++;
		if (data->cmd[i])
			printf(" ");
	}
	if (f != 0)
		printf("\n");
}
