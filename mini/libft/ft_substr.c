/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:36:57 by otamrani          #+#    #+#             */
/*   Updated: 2022/11/12 17:30:44 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	i = ft_strlen(s);
	if (len > i - start)
		len = i - start;
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
