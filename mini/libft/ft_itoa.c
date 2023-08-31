/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:30:51 by otamrani          #+#    #+#             */
/*   Updated: 2022/11/12 17:30:59 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long s)
{
	int	i;

	i = 0;
	if (s <= 0)
	{
		s *= -1;
		i++;
	}
	while (s > 0)
	{
		s /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	long	j;
	char	*str;

	j = n;
	i = count(n);
	if (j < 0)
		j *= -1;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i] = 0;
	while (i-- > 0)
	{
		if (n == 0)
			str[i] = 48;
		else if (j == 0 && i == 0)
			str[i] = '-';
		else
			str[i] = j % 10 + 48;
		j /= 10;
	}
	return (str);
}
