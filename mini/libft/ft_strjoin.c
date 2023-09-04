/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 03:01:25 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/04 11:15:19 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*p;
	int		i;
	if(s2 && !*s2)
		return(s2);
	i = 0;
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (0);
	if(s1)
	while (*s1)
		p[i++] = *s1++;
	if(s2)
	while (*s2)
		p[i++] = *s2++;
	p[i] = '\0';
	ft_lstadd(&g_lobal.hold, lst_new(0, s1, s2));
	ft_lstadd(&g_lobal.hold, lst_new(0, p, 0));
	return (p);
}
