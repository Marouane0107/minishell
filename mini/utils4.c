/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:40:07 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/17 02:18:54 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cheker(t_list *lst)
{
	if (lst->token == 0 || !lst->next || lst->token == 1)
		return (1);
	if (lst->token == -7)
		return (1);
	return (0);
}

void	er_amb(char *s)
{
	g_lobal.ex = 1;
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

void	ft_tfree(t_data *data, char *in)
{
	if (data)
	{
		free_data(data);
		data = NULL;
	}
	if (in)
		free(in);
}

int	flen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	short_f(t_data *tmp1, t_list **lst, t_list *tmp)
{
	if (tmp1->out > 1)
		close(tmp1->out);
	tmp1->out = openout(tmp);
	if (tmp1->out == -3)
		ft_skip(lst);
}
