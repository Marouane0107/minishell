/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:23:34 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/08 15:34:32 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ftlen(char *str)
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
	t_list	*tmp;

	tmp = *lst;
	if (!(*lst))
		return (-1);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->token);
}

int	pipe_red(char *c, t_list **lst)
{
	int	j;

	j = syntax_error(c);
	if (ft_strlen(c) >= 2 && c[0] == '|' && j > 0)
	{
		if (end_struct(lst) > 0)
			return (msg_error(*lst), 0);
		ft_lstadd_back(lst, ft_lstnew("|", 1));
		ft_lstadd_back(lst, ft_lstnew(c + 1, j));
	}
	else
	{
		if (end_struct(lst) > 1 || end_struct(lst) == j || j < 0)
			return (msg_error(*lst), 0);
		ft_lstadd_back(lst, ft_lstnew(c, j));
		if ((*lst)->token == 1)
			return (msg_error(*lst), 0);
	}
	return (1);
}

int	add_attach(char **c, t_list **lst)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (check_spacial(c[i]))
		{
			if (!pipe_red(c[i], lst))
				return (0);
		}
		else
		{
			if (!ft_word(c[i], lst))
				return (0);
		}
		i++;
	}
	return (1);
}

// check if the word is a special character and attached to it
int	detach_separted(char *str, t_list **lst)
{
	char	**c;
	int		i;
	int		m;

	i = 0;
	m = 0;
	c = (char **)malloc(sizeof(char *) * (ft_countd(str) + 1));
	while (str[i])
	{
		c[m] = ft_substr(str, i, ftlen(str + i));
		i = i + ft_strlen(c[m]);
		m++;
	}
	c[m] = NULL;
	ft_lstadd(&g_lobal.hold, lst_new(c, 0, 0));
	if (!add_attach(c, lst))
		return (0);
	return (1);
}
