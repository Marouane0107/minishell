/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:39:23 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/08 15:42:07 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str(char s)
{
	char	*c;

	c = malloc(sizeof(char) * 2);
	c[0] = s;
	c[1] = '\0';
	return (c);
}

int	adge_case(char *s, int j, char *q)
{
	if (q[j] < 0)
		return (0);
	if ((s[j] == '$' && s[j + 1] == '\"' && s[j + 2] != 0))
		return (1);
	if ((s[j] == '$' && s[j + 1] == '\'' && s[j + 2] != 0))
		return (1);
	return (0);
}

int	check_single(char *s, int j)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (s[i] && j > i)
	{
		if (s[i] == '\'')
			k++;
		i++;
	}
	if (k % 2 != 0)
		return (1);
	return (0);
}

int	get_exp(char *s, int j, char *q, int m)
{
	int	i;

	i = 0;
	if ((s[j] == '$' && check_single(q, j)) && m != 0)
		return (0);
	if (j - 1 >= 0 && s[j] == '$')
	{
		if (s[j - 1] == '$')
			return (0);
	}
	if (s[j] == '$')
	{
		j++;
		while (s[j] && s[j] != ' ' && s[j] != '\t' && s[j] != '`')
		{
			if ((s[j] >= 33 && s[j] <= 47) || (s[j] >= 58 && s[j] <= 64))
				break ;
			if ((s[j] >= 91 && s[j] <= 94) || (s[j] >= 123 && s[j] <= 126))
				break ;
			j++;
			i++;
		}
	}
	return (i);
}

char	*searsh_env(char *c, int j)
{
	t_env	*tmp;

	tmp = g_lobal.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, c))
		{
			if (ft_strchr(tmp->value, ' ') && j == 11)
				return (ft_strjoin("$", c));
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	if (j == 11)
		return (ft_strjoin("$", c));
	return (NULL);
}
