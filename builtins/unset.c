/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 09:36:19 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/03 20:39:05 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_unset(t_data *data)
{
	int i;
	t_env *tmp;
	t_env *tmp2;

	i = 1;
	tmp = g_lobal.env;
	if(ft_strcmp(tmp->name, data->cmd[i]) == 0)
	{
		g_lobal.env = tmp->next;
		tmp = g_lobal.env;
		i++;
	}
	while (tmp && tmp->next && data->cmd[i])
	{
		if (ft_strcmp((tmp)->next->name, data->cmd[i]) == 0)
		{
			tmp2 = (tmp)->next;
			tmp->next = (tmp)->next->next;
			free(tmp2);
			i++;
			tmp = g_lobal.env;
		}
		tmp = (tmp)->next;
	}
}

