/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 09:36:19 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/15 22:24:34 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"


void ft_lstremove(t_env **head, char *name)
{
	t_env *tmp;
	t_env *tmp2;

	tmp = *head;
	if (tmp && ft_strcmp(tmp->name, name) == 0)
	{
		*head = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->next->name, name) == 0)
		{
			tmp2 = tmp->next;
			tmp->next = tmp2->next;
			free(tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}
void	ft_unset(t_data *data)
{
	int i;
	i = 0;
	while(data->cmd[i])
	{
		ft_lstremove(&g_lobal.env, data->cmd[i]);
		i++;
	}

}
