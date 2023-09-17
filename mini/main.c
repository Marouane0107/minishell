/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:13 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/17 17:06:20 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_lobal;

int	main(int  ac, char **av)
{
	char	*input;
	t_data	*data;
	(void)av;
	if(ac > 1)
		exit(127);
	g_lobal.env = get_environ();
	g_lobal.ex = 0;
	data = NULL;
	input = NULL;
	g_lobal.i = 1;
	g_lobal.j = 0;
	parss(data, input);
	return (0);
}
