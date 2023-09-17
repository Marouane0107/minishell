/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 01:10:02 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/17 01:36:11 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_char(char c, char s)
{
	if (s == c)
		return (1);
	if (s < 0)
	{
		if (s == c)
			return (1);
	}
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s && !*s)
		return (1);
	while (s[i])
	{
		if (!check_char(s[0], c) && i == 0)
			count++;
		if (check_char(s[i], c) && !check_char(s[i + 1], c) && s[i + 1] != '\0')
		{
			count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_len(char const *s, char c, char **ps, int e)
{
	int	i;
	int	j;

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
		if (s[i] != 0)
			i++;
	}
	return (ps[j] = NULL, ps);
}

char	**ft_split(char const *s, char c)
{
	int		e;
	int		i;
	char	**p;

	if (!s)
		return (0);
	e = 0;
	i = ft_count(s, c);
	p = malloc(sizeof(char *) * (i + 1));
	if (!p)
		return (0);
	if (s && !*s)
	{
		p[0] = ft_strdup("");
		p[1] = 0;
	}
	else
		p = ft_len(s, c, p, e);
	ft_lstadd(&g_lobal.hold, lst_new(p, 0, 0));
	return (p);
}
// static char	**ft_len(char const *s, char c, char **ps)
// {
// 	int	i;
// 	int	j;
// 	int	e;

// 	e = 0;
// 	j = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		while (check_char(s[i], c))
// 			i++;
// 		if (!s[i])
// 			break ;
// 		e = i;
// 		while (!check_char(s[i], c) && s[i])
// 			i++;
// 		ps[j] = ft_substr(s, e, (i - e));
// 		if (ps[j] == 0)
// 			return (ffree(ps), NULL);
// 		j++;
// 	}
// 	ps[j] = 0;
// 	return (ps);
// }
