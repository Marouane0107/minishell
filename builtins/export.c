/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:30 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/17 01:24:53 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

int	name_check(char	*name)
{
	int	i;

	i = 0;
	if (name[0] >= 48 && name[0] <= 57)
	{
		printf("minishell: export: `%s': not a valid identifier\n", name);
		g_lobal.ex = 1;
		return (1);
	}
	while (name[i])
	{
		if ((name[i] >= 97 && name[i] <= 122)
			|| (name[i] >= 65 && name[i] <= 90)
			|| (name[i] >= 48 && name[i] <= 57)
			|| name[i] == '_' || name[i] == 92)
			i++;
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n", name);
			g_lobal.ex = 1;
			return (1);
		}
	}
	return (0);
}

char	*add_env_norm(t_data *data, char *s, char *name, int i)
{
	if (s[0] != '=' && s[i] == '=' && s[i - 1] == '+')
	{
		i--;
		data->f = 1;
	}
	name = ft_substr(s, 0, i);
	if (!*name)
	{
		printf("minishell: export: `%s': not a valid identifier\n",
			data->cmd[g_lobal.j]);
		g_lobal.ex = 1;
		return (0);
	}
	if (name_check(name))
		return (0);
	if (data->f == 1)
		i++;
	return (name);
}

void	ft_add_env(t_data *data, char *s)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	name = NULL;
	value = NULL;
	data->f = 0;
	while (s[i] && s[i] != '=')
		i++;
	name = add_env_norm(data, s, name, i);
	if (!name)
		return ;
	if (s[i] == '=')
	{
		i++;
		value = ft_substr(s, i, ft_strlen(s));
	}
	if (!ft_setenv(data, name, value))
		return ;
	else
		ft_lstdadd_back1(&g_lobal.env, ft_lstnew1(name, value));
}

void	print_export(void)
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
	int		i;

	i = 1;
	if (!data->cmd[1])
	{
		print_export();
		return ;
	}
	while (data->cmd[i])
	{
		g_lobal.j = i;
		ft_add_env(data, data->cmd[i++]);
	}
}
