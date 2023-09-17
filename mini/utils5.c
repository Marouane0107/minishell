/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:25:17 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/17 21:53:29 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstdadd_back1(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return (0);
	if (!(*lst))
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_grbg	*lst_new(char **p, char *name, char *value)
{
	t_grbg	*node;

	node = malloc(sizeof(t_grbg));
	if (!node)
		return (0);
	if (node)
	{
		node->l = p;
		node->p = name;
		node->s = value;
		node->next = NULL;
	}
	return (node);
}

t_env	*ft_lstnew1(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	if (node)
	{
		node->name = ft_strdup(name);
		node->value = ft_strdup(value);
		node->next = NULL;
	}
	return (node);
}

void	ft_exitcd(void)
{
	write(1, "exit\n", 6);
	exit(g_lobal.ex);
}
