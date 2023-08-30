/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:55:44 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/08 20:04:59 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ffree(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	putstr_fd(char *s, int fd, char *m)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
	i = 0;
	if (m)
	{
		while (m[i])
		{
			write(fd, &m[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2 && !n)
		return (0);
	while (((i < n) && (s1[i] || s2[i])))
	{
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(s2, "\n");
	while (s1[i] || tmp[i])
	{
		if (s1[i] != tmp[i])
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}
