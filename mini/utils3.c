/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:50:44 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/17 02:20:51 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_error(t_list *lst)
{
	int	i;

	g_lobal.ex = 1;
	i = end_struct(&lst);
	if (i == 1)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	if (lst)
		free_lst(lst);
}

int	ins(char c, int m, int j)
{
	if (m % 2 != 0 && c != '\"')
		return (1);
	else if (j % 2 != 0 && c != '\'')
		return (1);
	else
		return (0);
}

int	noption(t_list **lst)
{
	int		i;
	char	**s;

	s = NULL;
	i = 0;
	if ((*lst) && (*lst)->token == 1)
		(*lst) = (*lst)->next;
	while ((*lst))
	{
		if ((*lst)->token == 1)
			return (i);
		if ((*lst)->token == -7)
		{
			s = ft_split((*lst)->content, ' ');
			i += flen(s);
		}
		else
			i++;
		(*lst) = (*lst)->next;
	}
	return (i);
}

void	allocate(t_data **data, int i, t_list *tmp1)
{
	int	j;

	j = 0;
	while (i > 0)
	{
		j = noption(&tmp1);
		ft_lstadd_back2(data, ft_lstnew2(0, 1, j + 1));
		i--;
	}
}

t_data	*convert_lst(t_list *lst)
{
	char	**s;
	t_list	*tm;
	t_data	*data;

	data = NULL;
	tm = lst;
	allocate(&data, count_x(lst, 1), tm);
	s = open_here(lst);
	fill(&data, lst, s);
	ffree(s);
	return (data);
}
