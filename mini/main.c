/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:13 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/16 00:21:58 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_lobal;

int	main(void)
{	
	char *input;
	t_data *data;
	g_lobal.env = get_environ();
	g_lobal.ex = 0;
	data = NULL;
	input = NULL;
	g_lobal.i = 1;
	g_lobal.j = 0;
	parss(data , input);
	return (0);
}
