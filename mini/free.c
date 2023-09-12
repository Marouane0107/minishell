/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:16:04 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/08 15:45:25 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = (env);
		(env) = (env)->next;
		if (env)
		{
			free(tmp->name);
			free(tmp->value);
		}
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data;
		data = data->next;
		free(tmp);
	}
}

void	free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
