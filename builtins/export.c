/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:30 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/24 00:04:26 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_add_env(t_data *data, char *s)
{
	char	*name;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '=')
		i++;
	name = ft_substr(s, 0, i);
	if (s[i] == '=')
		i++;
	value = ft_substr(s, i, ft_strlen(s));
	ft_lstadd_back(&data->env, ft_lstnew(ft_lstnew_env(name, value)));
	free(name);
	free(value);
}

void	ft_export(t_data *data)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = data->env;
	if (!data->cmd[1])
	{
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		while (data->cmd[i])
		{
			if (ft_strchr(data->cmd[i], '='))
				ft_add_env(data, data->cmd[i]);
			else
				ft_add_env(data, data->cmd[i]);
			i++;
		}
	}
}
