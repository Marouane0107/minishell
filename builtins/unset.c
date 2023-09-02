/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 09:36:19 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/02 18:33:20 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_unset(t_data *data)
{
	int i;
	t_env *tmp;

	i = 1;
	tmp = data->env;
	
	while (tmp && tmp->next && data->cmd[i])
	{
		if(ft_strcmp(tmp->name, data->cmd[i]) == 0)
		{
			data->env = tmp->next;
			tmp = data->env;
			i++;
		}
		if (ft_strcmp((tmp)->next->name, data->cmd[i]) == 0)
		{
			tmp->next = (tmp)->next->next;
			i++;
			tmp = data->env;
		}
		tmp = (tmp)->next;
	}
}

