/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:54:30 by otamrani          #+#    #+#             */
/*   Updated: 2022/11/12 17:30:47 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	if (!s1 || !set)
		return (0);
	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
		return (ft_strdup(s1));
	while (s1[i])
	{
		if ((ft_strchr(set, s1[i]) == 0))
			break ;
		i++;
	}
	j = ft_strlen(s1) - 1;
	while (j != 0)
	{
		if (ft_strchr(set, s1[j]) == 0)
			break ;
		j--;
	}
	p = ft_substr(s1, i, (j - i) + 1);
	return (p);
}
