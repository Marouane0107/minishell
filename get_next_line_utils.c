/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:52:05 by otamrani          #+#    #+#             */
/*   Updated: 2023/04/05 22:26:11 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || s == '\0')
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (0);
	if (s1)
		while (*s1)
			p[i++] = *s1++;
	if (s2)
		while (*s2)
			p[i++] = *s2++;
	p[i] = '\0';
	return (p);
}

char	*ft_get_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (ft_substr(s, 0, (i + 1)));
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	size_t	len;
	size_t	i;
	char	*p;

	i = 0;
	len = ft_strlen(s1);
	p = malloc(sizeof(char) * len + 1);
	if (p == 0)
		return (0);
	if (s1 && (*s1))
	{
		while (s1[i])
		{
			p[i] = s1[i];
			i++;
		}
	}
	p[i] = 0;
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	while (s[start] && len > 0)
	{
		p[j++] = s[start++];
		len--;
	}
	p[j] = 0;
	return (p);
}
