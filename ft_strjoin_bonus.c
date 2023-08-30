/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:16:41 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/08 20:16:57 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	free(&s1);
	return (p);
}
