/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:56:20 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/08 15:39:43 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_expend(char *s, t_list **lst, int j)
{
	int		i;
	char	*c;
	char	*all;
	char	*q;

	i = 0;
	(void)lst;
	all = ft_strdup("");
	q = ft_strdup(s);
	quote(q);
	while (q[i])
	{
		if (adge_case(q, i, s) && j)
			i++;
		else if (get_exp(q, i, s, j) && j != 2)
		{
			c = ft_substr(q, i + 1, get_exp(q, i, s, j));
			all = ft_strjoin(all, searsh_env(c, j));
			i += ft_strlen(c);
		}
		else if ((s[i] != '\'' && s[i] != '\"') || !j)
			all = ft_strjoin(all, ft_str(q[i]));
		i++;
	}
	return (free(q), ft_lstadd(&g_lobal.hold, lst_new(0, all, 0)), all);
}

void	ex_status(char **s)
{
	int		i;
	int		j;
	char	*c;
	char	*tmp;

	i = 0;
	j = 1;
	if (!s || !(*s))
		return ;
	while ((*s)[i])
	{
		if ((*s)[i] == '$' && (*s)[i + 1] == '?' && (j % 2))
		{
			c = ft_itoa(g_lobal.ex);
			tmp = ft_strjoin(c, ft_substr((*s), i + 2, ft_strlen((*s))));
			(*s) = ft_strjoin(ft_substr((*s), 0, i), tmp);
		}
		if ((*s)[i] == '$' && (*s)[i + 1] == '$')
			j++;
		i++;
	}
	ft_lstadd(&g_lobal.hold, lst_new(0, c, 0));
}

int	ambigus(char *s, t_list **lst)
{
	if (!ft_strcmp(s, "$"))
		return (0);
	if (ft_strchr(s, '\'') || ft_strchr(s, '\"'))
		return (0);
	if (end_struct(lst) == 3 || end_struct(lst) == 4)
		return (1);
	return (0);
}

void	ofherdoc(char *s, t_list **lst)
{
	char	*wexp;

	wexp = check_expend(s, lst, 2);
	if (ft_strchr(s, '\'') || ft_strchr(s, '\"'))
		ft_lstadd_back(lst, ft_lstnew(wexp, -2));
	else
		ft_lstadd_back(lst, ft_lstnew(wexp, -1));
}

int	ft_word(char *s, t_list **lst)
{
	char	*wexp;

	if (end_struct(lst) == 5)
		return (ofherdoc(s, lst), 1);
	if (ambigus(s, lst))
	{
		wexp = check_expend(s, lst, 11);
		ex_status(&wexp);
		if (wexp[0] == '$')
			ft_lstadd_back(lst, ft_lstnew(wexp, -3));
		ft_lstadd_back(lst, ft_lstnew(wexp, -1));
		return (1);
	}
	wexp = check_expend(s, lst, 1);
	ex_status(&wexp);
	if (end_struct(lst) > 1)
		ft_lstadd_back(lst, ft_lstnew(wexp, -1));
	else
		ft_lstadd_back(lst, ft_lstnew(wexp, 0));
	return (1);
}
