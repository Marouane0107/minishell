/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:02:42 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/02 20:39:56 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchrr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	check_spacial(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|' || s[i] == '>' || s[i] == '<')
			return (1);
		i++;
	}
	return (0);
}
// // for filtering error of speacial characters
int	syntax_error(char *s)
{
	if (ft_strcmp(s, "|") == 0)
		return (1);
	else if (ft_strcmp(s, "|>") == 0)
		return (3);
	else if (ft_strcmp(s, "|<<") == 0)
		return (5);
	else if (ft_strcmp(s, "|>>") == 0)
		return (4);
	else if (ft_strcmp(s, "|<") == 0)
		return (2);
	else if (ft_strcmp(s, ">") == 0)
		return (3);
	else if (ft_strcmp(s, "<") == 0)
		return (2);
	else if (ft_strcmp(s, ">>") == 0)
		return (4);
	else if (ft_strcmp(s, "<<") == 0)
		return (5);
	return (-1);
}

int	ft_countd(char *str)
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

void	add_node(t_list **head, char *content, int token)
{
	t_list *new;
	t_list *tmp;

	new = malloc(sizeof(t_list));
	new->content = content;
	new->token = token;
	new->next = NULL;
	if (!(*head) || !head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}