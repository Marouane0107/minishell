/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:16:04 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/16 04:08:27 by maouzal          ###   ########.fr       */
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
char *open_rand()
{
	char rand[3];
	char *her;
	int i;
	i = open("/dev/random", O_RDWR);
	read(i, rand, 2);
	her = ft_strjoin("/tmp/", rand);
	close(i);
	return(her);
}
