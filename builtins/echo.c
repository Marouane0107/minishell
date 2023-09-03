/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:09 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/03 14:29:44 by maouzal          ###   ########.fr       */
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
	f = 0;
	if(!data->cmd[1])
	{
		printf("\n");
		return;
	}
	if (data->cmd[1][0] == '-' && data->cmd[1][1] =='n')
	{
		while (data->cmd[1][j] == 'n')
			j++;
		if (data->cmd[1][j] == '\0')
			f = 1;
	}
	if (f == 1)
		i++;
	while (data->cmd && data->cmd[i])
	{
		printf("%s",data->cmd[i]);
		i++;
		if (data->cmd[i])
			printf(" ");
	}
	if (f != 1)
		printf("\n");
}
