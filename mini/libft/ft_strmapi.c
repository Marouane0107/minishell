/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 01:17:04 by otamrani          #+#    #+#             */
/*   Updated: 2022/11/12 18:15:38 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ps;

	if (!s)
		return (0);
	i = ft_strlen(s);
	ps = malloc(sizeof(char) * (i + 1));
	if (!ps)
		return (0);
	i = 0;
	while (s[i])
	{
		ps[i] = s[i];
		i++;
	}
	ps[i] = '\0';
	i = 0;
	while (ps[i])
	{
		ps[i] = f(i, ps[i]);
		i++;
	}
	return (ps);
}
