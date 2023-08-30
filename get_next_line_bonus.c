/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:13:18 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/08 20:27:33 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **s1, char **s2)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = 0;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = 0;
	}
}

char	*ft_chkline(char **buffer1, ssize_t j)
{
	char		*sline;
	char		*tmp;
	static char	*rest;

	if (j < 0)
		return (ft_free(buffer1, &rest), NULL);
	tmp = rest;
	rest = ft_strjoin(rest, *buffer1);
	ft_free(&tmp, 0);
	sline = ft_get_line(rest);
	if (sline)
	{
		tmp = rest;
		rest = ft_strdup(rest + ft_strlen(sline));
		return (ft_free(&tmp, buffer1), sline);
	}
	if (j == 0)
	{
		if (rest && *rest)
			sline = ft_strdup(rest);
		return (ft_free(&rest, buffer1), sline);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*result;
	ssize_t	i;

	result = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	i = read(fd, buffer, BUFFER_SIZE);
	if (i < 0)
		return (ft_chkline(&buffer, i), NULL);
	while (i >= 0)
	{
		buffer[i] = 0;
		result = ft_chkline(&buffer, i);
		if (!result && !buffer)
			return (0);
		if (result && *result)
			return (ft_free(0, &buffer), result);
		i = read(fd, buffer, BUFFER_SIZE);
	}
	return (0);
}
