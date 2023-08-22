/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:23:34 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/22 22:27:05 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count(char *str)
{
	int	i;
	int	m;

	i = 0;
	m = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			while (str[i] == '|' || str[i] == '>' || str[i] == '<')
				i++;
			m++;
		}
		else if (str[i] != '|' && str[i] != '>' && str[i] != '<')
		{
			while (str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i])
			{
				i++;
			}
			m++;
		}
	}
	return (m);
}

int	ft_len(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		while (str[i] == '|' || str[i] == '>' || str[i] == '<')
			i++;
	else
		while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<')
			i++;
	return (i);
}

int	end_struct(t_list **lst)
{
	t_list *tmp;
	tmp = *lst;
	if (!lst || !(*lst))
		return (-1);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->token);
}


int	pipe_red(char *c, t_env *env, t_list **lst)
{
	int		j;
	
	j = syntax_error(c);
	if (ft_strlen(c) >= 2 && c[0] == '|' && j)
	{
		if (end_struct(lst) > 0)
		{
			ft_putstr_fd("syntax error P\n", 2);
			return (0);
		}
		ft_lstadd_back(lst, ft_lstnew("|", 1, env));
		ft_lstadd_back(lst, ft_lstnew(c + 1, j, env));
	}
	else
	{
		if (end_struct(lst) > 1 || end_struct(lst) == j  || j < 0)
		{
			ft_putstr_fd("syntax errorT\n", 2);
			return (0);
		}
		ft_lstadd_back(lst, ft_lstnew(c, j, env));
	}
	return (1);
}

int	add_attach(char **c, t_env *env, t_list **lst)
{
	int	i;


	i = 0;
	while (c[i])
	{
		if (check_spacial(c[i]))
		{
			if (!pipe_red(c[i], env, lst))
				return (0);
		}
		else
		{
			if(!ft_word(c[i], env, lst))
				return (0);
			// ft_lstadd_back(lst, ft_lstnew(c[i], 0));
		}
		i++;
	}
	return (1);
}
//check if the word is a special character and attached to it
int	detach_separted(char *str, t_env *env, t_list **lst)
{
	char **c;

	int i;
	int m;
	i = 0;
	m = 0;
	c = (char **)malloc(sizeof(char *) * (ft_count(str) + 1));
	while (str[i])
	{
		c[m] = ft_substr(str, i, ft_len(str + i));
		i = i + ft_strlen(c[m]);
		m++;
	}
	c[m] = NULL;
	if (!add_attach(c, env, lst))
		return (0);
	return (1);
}