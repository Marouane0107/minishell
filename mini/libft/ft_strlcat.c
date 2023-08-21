/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:50:45 by otamrani          #+#    #+#             */
/*   Updated: 2022/11/12 17:31:32 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ld;
	size_t	ls;
	size_t	i;

	i = 0;
	if (!dstsize && !dst && src != 0)
		return (0);
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	if (dstsize == 0 || ld >= dstsize)
		return (ls + dstsize);
	while (src[i] && i < dstsize - ld - 1)
	{
		dst[ld + i] = src[i];
		i++;
	}
	dst[ld + i] = '\0';
	return (ld + ls);
}
