/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:30 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/02 11:43:34 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void ft_add_env(t_data *data, char *s)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	data->f = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=' && s[i - 1] == '+')
	{
		i--;
		data->f = 1;
	}
	name = ft_substr(s, 0, i);
	if (data->f == 1)
		i++;
	if (s[i] == '=')
	{
		i++;
		value = ft_substr(s, i, ft_strlen(s));
	}
	if (!ft_setenv(name, value))
		return ;
	else 
		ft_lstdadd_back1(&g_lobal.env, ft_lstnew1(name, value));
}

void	print_export()
{
	t_env	*tmp;

	tmp = g_lobal.env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
}

void	ft_export(t_data *data)
{
	int	i;

	i = 1;
	if (!data->cmd[1])
	{
		print_export(data);
		return ;
	}
	if ((data->cmd[1][0] >= 97 && data->cmd[1][0] <= 122)
		|| (data->cmd[1][0] >= 65 && data->cmd[1][0] <= 90))
	{	
		while (data->cmd[i])
			ft_add_env(data, data->cmd[i++]);
	}
	else
	{
		printf("minishell: export: `%s': not a valid identifier\n", data->cmd[1]);
		return ;
	}
}
