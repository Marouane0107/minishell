/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 01:10:02 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/26 01:47:28 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ffree(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[0] != c && i == 0)
			count++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			count++;
		}
		i++;
	}
	return (count);
}
int check_char(char c, char s)
{
	if(s < 0)
	{
		if(c == s)
			return(1);
		return(0);
	}
	if(c == s)
		return (1);
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
static char	**ft_len(char const *s, char c, char **ps)
{
	int	i;
	int	j;
	int	e;

	e = 0;
	j = 0;
	i = 0;
	while (s[i])
	{
		e = i;
		while (!check_char(s[i], c) && s[i])
		{
			i++;
			if (check_char(s[i], c) || s[i] == '\0')
			{
				ps[j] = ft_substr(s, e, (i - e));
				if (ps[j] == 0)
					return (ffree(ps), NULL);
				j++;
			}
		}
		(s[i] != 0) && (i++);
	}
	return (ps[j] = 0, ps);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**p;

	if (!s)
		return (0);
	i = ft_count(s, c);
	p = malloc(sizeof(char *) * (i + 1));
	if (!p)
		return (0);
	p = ft_len(s, c, p);
	return (p);
}
