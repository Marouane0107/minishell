/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:02:42 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/16 23:13:27 by otamrani         ###   ########.fr       */
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
	else if (ft_strcmp(s, ">")== 0)
		return (3);
	else if (ft_strcmp(s, "<") == 0)
		return (2);
	else if (ft_strcmp(s, ">>") == 0)
		return (4);
	else if (ft_strcmp(s, "<<") == 0)
		return (5);
	return (-1);
}
// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] || s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

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