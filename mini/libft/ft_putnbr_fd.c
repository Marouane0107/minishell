/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:17:32 by otamrani          #+#    #+#             */
/*   Updated: 2022/11/12 17:31:06 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	j;

	j = n;
	if (j < 0)
	{
		ft_putchar_fd('-', fd);
		j *= -1;
	}
	if (j > 9)
	{
		ft_putnbr_fd(j / 10, fd);
		ft_putnbr_fd(j % 10, fd);
	}
	if (j < 10)
	{
		ft_putchar_fd((j + 48), fd);
	}
}
