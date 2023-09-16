/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filldata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:23:23 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/16 18:55:49 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	openin(t_list *tmp, char **s, int j)
{
	int		fd;
	char   *rand;
	
	rand = NULL;
	fd = 0;
	if (tmp->token == 5 && !g_lobal.g)
	{
		rand = open_rand();
		fd = open(rand, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror("open"), -3);
		ft_putstr_fd(s[j], fd);
		close(fd);
		fd = open(rand, O_RDONLY);
	}
	else if (!g_lobal.g)
	{
		fd = open(tmp->next->content, O_RDONLY);
		if (fd == -1)
			return (perror("open"), -3);
	}
	return (fd);
}

void er_amb(char *s)
{
	g_lobal.ex = 1;
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

int	openout(t_list *lst)
{
	int		fd;

	fd = 1;
	if (lst->token == 3 && !g_lobal.g)
	{
		fd = open(lst->next->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror("open"), -3);
	}
	else if (lst->token == 4 && !g_lobal.g)
	{
		fd = open(lst->next->content, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror("open"), -3);
	}
	return (fd);
}

void	handle_tokens(t_list **lst, t_data **data, char **s, int j)
{
	t_list	*tmp;
	t_data	*tmp1;

	tmp1 = *data;
	tmp = *lst;
	if(tmp->next->token == -3)
	{
		tmp1->in = -3;
		er_amb(tmp->next->content);
		ft_skip(lst);
		return ;
	}
	if (tmp->token == 2 || tmp->token == 5)
	{
		if (tmp1->in > 1)
			close(tmp1->in);
		tmp1->in = openin(tmp, s, j);
		if (tmp1->in == -3)
			ft_skip(lst);
	}
	else if (tmp->token == 4 || tmp->token == 3)
	{
		if (tmp1->out > 1)
			close(tmp1->out);
		tmp1->out = openout(tmp);
		if (tmp1->out == -3)
			ft_skip(lst);
	}
}

void	add_cmd(t_list *lst, t_data **tmp)
{
	char **s;

	s = NULL;
	if (lst && lst->token == 1)
		g_lobal.n = 0;
	if(lst->token == -7)
	{
		s = ft_split(lst->content, ' ');
		while(*s)
			(*tmp)->cmd[g_lobal.n++] = *s++;
	}
	else if ((*tmp) && (*tmp)->cmd && lst->token == 0)
	{
		(*tmp)->cmd[g_lobal.n] = lst->content;
		g_lobal.n++;
	}
}

int cheker(t_list *lst)
{
	if(lst->token == 0 || !lst->next || lst->token == 1)
		return(1);
	if(lst->token == -7)
		return(1);
	return(0);
}

void	fill(t_data **data, t_list *lst, char **s)
{
	t_data	*tmp;
	int		j;

	j = 0;
	tmp = *data;
	g_lobal.n = 0;
	while (lst)
	{
		if (cheker(lst))
			add_cmd(lst, &tmp);
		if (lst->token == 1)
		{
			if (tmp->out == 1)
				tmp->out = -1;
			tmp = tmp->next;
			tmp->in = -2;
		}
		else if (lst->token > 1)
		{
			handle_tokens(&lst, &tmp, s, j);
			if (lst && lst->token == 5)
				j++;
		}
		lst = lst->next;
	}
}

//need to fix norm