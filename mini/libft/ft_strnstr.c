/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:29:50 by otamrani          #+#    #+#             */
/*   Updated: 2022/11/12 17:31:44 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lettle, size_t len)
{
	size_t	s;
	size_t	i;

	i = 0;
	s = 0;
	if (!big && !len && lettle != 0)
		return (0);
	if (*(lettle) == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		s = 0;
		while (big[i + s] == lettle[s] && (i + s < len))
		{
			s++;
			if (lettle[s] == '\0')
			{
				return ((char *)big + i);
			}
		}
		i++;
	}
	return (0);
}
